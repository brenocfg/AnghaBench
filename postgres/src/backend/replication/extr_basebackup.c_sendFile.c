#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
struct stat {int st_size; } ;
typedef  int pgoff_t ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  pd_checksum; } ;
typedef  TYPE_1__* PageHeader ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char const*,char*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int BLCKSZ ; 
 int /*<<< orphan*/  CHECK_FREAD_ERROR (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ DataChecksumsEnabled () ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,size_t) ; 
 int Min (int,int) ; 
 scalar_t__ PageGetLSN (char*) ; 
 int /*<<< orphan*/  PageIsNew (char*) ; 
 int RELSEG_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int TAR_SEND_SIZE ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  _tarWriteHeader (char const*,int /*<<< orphan*/ *,struct stat*,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  errmsg_plural (char*,char*,int,char const*,int) ; 
 scalar_t__ errno ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_checksummed_file (char const*,char*) ; 
 char* last_dir_separator (char const*) ; 
 int /*<<< orphan*/  noverify_checksums ; 
 int /*<<< orphan*/  pg_checksum_page (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_report_checksum_failures_in_db (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pq_putmessage (char,char*,size_t) ; 
 scalar_t__ startptr ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  throttle (int) ; 
 int total_checksum_failures ; 

__attribute__((used)) static bool
sendFile(const char *readfilename, const char *tarfilename, struct stat *statbuf,
		 bool missing_ok, Oid dboid)
{
	FILE	   *fp;
	BlockNumber blkno = 0;
	bool		block_retry = false;
	char		buf[TAR_SEND_SIZE];
	uint16		checksum;
	int			checksum_failures = 0;
	off_t		cnt;
	int			i;
	pgoff_t		len = 0;
	char	   *page;
	size_t		pad;
	PageHeader	phdr;
	int			segmentno = 0;
	char	   *segmentpath;
	bool		verify_checksum = false;

	fp = AllocateFile(readfilename, "rb");
	if (fp == NULL)
	{
		if (errno == ENOENT && missing_ok)
			return false;
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\": %m", readfilename)));
	}

	_tarWriteHeader(tarfilename, NULL, statbuf, false);

	if (!noverify_checksums && DataChecksumsEnabled())
	{
		char	   *filename;

		/*
		 * Get the filename (excluding path).  As last_dir_separator()
		 * includes the last directory separator, we chop that off by
		 * incrementing the pointer.
		 */
		filename = last_dir_separator(readfilename) + 1;

		if (is_checksummed_file(readfilename, filename))
		{
			verify_checksum = true;

			/*
			 * Cut off at the segment boundary (".") to get the segment number
			 * in order to mix it into the checksum.
			 */
			segmentpath = strstr(filename, ".");
			if (segmentpath != NULL)
			{
				segmentno = atoi(segmentpath + 1);
				if (segmentno == 0)
					ereport(ERROR,
							(errmsg("invalid segment number %d in file \"%s\"",
									segmentno, filename)));
			}
		}
	}

	while ((cnt = fread(buf, 1, Min(sizeof(buf), statbuf->st_size - len), fp)) > 0)
	{
		/*
		 * The checksums are verified at block level, so we iterate over the
		 * buffer in chunks of BLCKSZ, after making sure that
		 * TAR_SEND_SIZE/buf is divisible by BLCKSZ and we read a multiple of
		 * BLCKSZ bytes.
		 */
		Assert(TAR_SEND_SIZE % BLCKSZ == 0);

		if (verify_checksum && (cnt % BLCKSZ != 0))
		{
			ereport(WARNING,
					(errmsg("could not verify checksum in file \"%s\", block "
							"%d: read buffer size %d and page size %d "
							"differ",
							readfilename, blkno, (int) cnt, BLCKSZ)));
			verify_checksum = false;
		}

		if (verify_checksum)
		{
			for (i = 0; i < cnt / BLCKSZ; i++)
			{
				page = buf + BLCKSZ * i;

				/*
				 * Only check pages which have not been modified since the
				 * start of the base backup. Otherwise, they might have been
				 * written only halfway and the checksum would not be valid.
				 * However, replaying WAL would reinstate the correct page in
				 * this case. We also skip completely new pages, since they
				 * don't have a checksum yet.
				 */
				if (!PageIsNew(page) && PageGetLSN(page) < startptr)
				{
					checksum = pg_checksum_page((char *) page, blkno + segmentno * RELSEG_SIZE);
					phdr = (PageHeader) page;
					if (phdr->pd_checksum != checksum)
					{
						/*
						 * Retry the block on the first failure.  It's
						 * possible that we read the first 4K page of the
						 * block just before postgres updated the entire block
						 * so it ends up looking torn to us.  We only need to
						 * retry once because the LSN should be updated to
						 * something we can ignore on the next pass.  If the
						 * error happens again then it is a true validation
						 * failure.
						 */
						if (block_retry == false)
						{
							/* Reread the failed block */
							if (fseek(fp, -(cnt - BLCKSZ * i), SEEK_CUR) == -1)
							{
								ereport(ERROR,
										(errcode_for_file_access(),
										 errmsg("could not fseek in file \"%s\": %m",
												readfilename)));
							}

							if (fread(buf + BLCKSZ * i, 1, BLCKSZ, fp) != BLCKSZ)
							{
								/*
								 * If we hit end-of-file, a concurrent
								 * truncation must have occurred, so break out
								 * of this loop just as if the initial fread()
								 * returned 0. We'll drop through to the same
								 * code that handles that case. (We must fix
								 * up cnt first, though.)
								 */
								if (feof(fp))
								{
									cnt = BLCKSZ * i;
									break;
								}

								ereport(ERROR,
										(errcode_for_file_access(),
										 errmsg("could not reread block %d of file \"%s\": %m",
												blkno, readfilename)));
							}

							if (fseek(fp, cnt - BLCKSZ * i - BLCKSZ, SEEK_CUR) == -1)
							{
								ereport(ERROR,
										(errcode_for_file_access(),
										 errmsg("could not fseek in file \"%s\": %m",
												readfilename)));
							}

							/* Set flag so we know a retry was attempted */
							block_retry = true;

							/* Reset loop to validate the block again */
							i--;
							continue;
						}

						checksum_failures++;

						if (checksum_failures <= 5)
							ereport(WARNING,
									(errmsg("checksum verification failed in "
											"file \"%s\", block %d: calculated "
											"%X but expected %X",
											readfilename, blkno, checksum,
											phdr->pd_checksum)));
						if (checksum_failures == 5)
							ereport(WARNING,
									(errmsg("further checksum verification "
											"failures in file \"%s\" will not "
											"be reported", readfilename)));
					}
				}
				block_retry = false;
				blkno++;
			}
		}

		/* Send the chunk as a CopyData message */
		if (pq_putmessage('d', buf, cnt))
			ereport(ERROR,
					(errmsg("base backup could not send data, aborting backup")));

		len += cnt;
		throttle(cnt);

		if (feof(fp) || len >= statbuf->st_size)
		{
			/*
			 * Reached end of file. The file could be longer, if it was
			 * extended while we were sending it, but for a base backup we can
			 * ignore such extended data. It will be restored from WAL.
			 */
			break;
		}
	}

	CHECK_FREAD_ERROR(fp, readfilename);

	/* If the file was truncated while we were sending it, pad it with zeros */
	if (len < statbuf->st_size)
	{
		MemSet(buf, 0, sizeof(buf));
		while (len < statbuf->st_size)
		{
			cnt = Min(sizeof(buf), statbuf->st_size - len);
			pq_putmessage('d', buf, cnt);
			len += cnt;
			throttle(cnt);
		}
	}

	/*
	 * Pad to 512 byte boundary, per tar format requirements. (This small
	 * piece of data is probably not worth throttling.)
	 */
	pad = ((len + 511) & ~511) - len;
	if (pad > 0)
	{
		MemSet(buf, 0, pad);
		pq_putmessage('d', buf, pad);
	}

	FreeFile(fp);

	if (checksum_failures > 1)
	{
		ereport(WARNING,
				(errmsg_plural("file \"%s\" has a total of %d checksum verification failure",
							   "file \"%s\" has a total of %d checksum verification failures",
							   checksum_failures,
							   readfilename, checksum_failures)));

		pgstat_report_checksum_failures_in_db(dboid, checksum_failures);
	}

	total_checksum_failures += checksum_failures;

	return true;
}