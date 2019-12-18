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
typedef  int uint32 ;
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  pg_crc32c ;
typedef  int /*<<< orphan*/  TwoPhaseRecordOnDisk ;
struct TYPE_2__ {scalar_t__ magic; int total_len; } ;
typedef  TYPE_1__ TwoPhaseFileHeader ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CRC32C (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ CloseTransientFile (int) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EQ_CRC32C (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FIN_CRC32C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_CRC32C (int /*<<< orphan*/ ) ; 
 int MAXALIGN (int) ; 
 int MAXPGPATH ; 
 int MaxAllocSize ; 
 int O_RDONLY ; 
 int OpenTransientFile (char*,int) ; 
 int PG_BINARY ; 
 scalar_t__ TWOPHASE_MAGIC ; 
 int /*<<< orphan*/  TwoPhaseFilePath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_TWOPHASE_FILE_READ ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 int /*<<< orphan*/  errmsg_plural (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static char *
ReadTwoPhaseFile(TransactionId xid, bool missing_ok)
{
	char		path[MAXPGPATH];
	char	   *buf;
	TwoPhaseFileHeader *hdr;
	int			fd;
	struct stat stat;
	uint32		crc_offset;
	pg_crc32c	calc_crc,
				file_crc;
	int			r;

	TwoPhaseFilePath(path, xid);

	fd = OpenTransientFile(path, O_RDONLY | PG_BINARY);
	if (fd < 0)
	{
		if (missing_ok && errno == ENOENT)
			return NULL;

		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\": %m", path)));
	}

	/*
	 * Check file length.  We can determine a lower bound pretty easily. We
	 * set an upper bound to avoid palloc() failure on a corrupt file, though
	 * we can't guarantee that we won't get an out of memory error anyway,
	 * even on a valid file.
	 */
	if (fstat(fd, &stat))
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not stat file \"%s\": %m", path)));

	if (stat.st_size < (MAXALIGN(sizeof(TwoPhaseFileHeader)) +
						MAXALIGN(sizeof(TwoPhaseRecordOnDisk)) +
						sizeof(pg_crc32c)) ||
		stat.st_size > MaxAllocSize)
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg_plural("incorrect size of file \"%s\": %zu byte",
							   "incorrect size of file \"%s\": %zu bytes",
							   (Size) stat.st_size, path,
							   (Size) stat.st_size)));

	crc_offset = stat.st_size - sizeof(pg_crc32c);
	if (crc_offset != MAXALIGN(crc_offset))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("incorrect alignment of CRC offset for file \"%s\"",
						path)));

	/*
	 * OK, slurp in the file.
	 */
	buf = (char *) palloc(stat.st_size);

	pgstat_report_wait_start(WAIT_EVENT_TWOPHASE_FILE_READ);
	r = read(fd, buf, stat.st_size);
	if (r != stat.st_size)
	{
		if (r < 0)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not read file \"%s\": %m", path)));
		else
			ereport(ERROR,
					(errmsg("could not read file \"%s\": read %d of %zu",
							path, r, (Size) stat.st_size)));
	}

	pgstat_report_wait_end();

	if (CloseTransientFile(fd) != 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not close file \"%s\": %m", path)));

	hdr = (TwoPhaseFileHeader *) buf;
	if (hdr->magic != TWOPHASE_MAGIC)
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("invalid magic number stored in file \"%s\"",
						path)));

	if (hdr->total_len != stat.st_size)
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("invalid size stored in file \"%s\"",
						path)));

	INIT_CRC32C(calc_crc);
	COMP_CRC32C(calc_crc, buf, crc_offset);
	FIN_CRC32C(calc_crc);

	file_crc = *((pg_crc32c *) (buf + crc_offset));

	if (!EQ_CRC32C(calc_crc, file_crc))
		ereport(ERROR,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("calculated CRC checksum does not match value stored in file \"%s\"",
						path)));

	return buf;
}