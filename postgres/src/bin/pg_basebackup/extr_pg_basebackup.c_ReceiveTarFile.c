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
typedef  int /*<<< orphan*/  zerobuf ;
typedef  int pgoff_t ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/ * gzFile ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_2__ {int len; char* data; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXPGPATH ; 
 scalar_t__ MINIMUM_VERSION_FOR_RECOVERY_GUC ; 
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PGRES_COPY_OUT ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int PQgetCopyData (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 int PQgetisnull (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQserverVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITE_TAR_DATA (char*,int) ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* basedir ; 
 scalar_t__ compresslevel ; 
 int /*<<< orphan*/  dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  get_gz_error (int /*<<< orphan*/ *) ; 
 scalar_t__ gzclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gzdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gzopen (char*,char*) ; 
 scalar_t__ gzsetparams (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pg_file_create_mode ; 
 int /*<<< orphan*/  pg_log_error (char*,char*,...) ; 
 int /*<<< orphan*/  progress_report (int,char*,int) ; 
 int read_tar_number (char*,int) ; 
 TYPE_1__* recoveryconfcontents ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  tarCreateHeader (char*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int totaldone ; 
 scalar_t__ writerecoveryconf ; 

__attribute__((used)) static void
ReceiveTarFile(PGconn *conn, PGresult *res, int rownum)
{
	char		filename[MAXPGPATH];
	char	   *copybuf = NULL;
	FILE	   *tarfile = NULL;
	char		tarhdr[512];
	bool		basetablespace = PQgetisnull(res, rownum, 0);
	bool		in_tarhdr = true;
	bool		skip_file = false;
	bool		is_recovery_guc_supported = true;
	bool		is_postgresql_auto_conf = false;
	bool		found_postgresql_auto_conf = false;
	int			file_padding_len = 0;
	size_t		tarhdrsz = 0;
	pgoff_t		filesz = 0;

#ifdef HAVE_LIBZ
	gzFile		ztarfile = NULL;
#endif

	/* recovery.conf is integrated into postgresql.conf in 12 and newer */
	if (PQserverVersion(conn) < MINIMUM_VERSION_FOR_RECOVERY_GUC)
		is_recovery_guc_supported = false;

	if (basetablespace)
	{
		/*
		 * Base tablespaces
		 */
		if (strcmp(basedir, "-") == 0)
		{
#ifdef WIN32
			_setmode(fileno(stdout), _O_BINARY);
#endif

#ifdef HAVE_LIBZ
			if (compresslevel != 0)
			{
				ztarfile = gzdopen(dup(fileno(stdout)), "wb");
				if (gzsetparams(ztarfile, compresslevel,
								Z_DEFAULT_STRATEGY) != Z_OK)
				{
					pg_log_error("could not set compression level %d: %s",
								 compresslevel, get_gz_error(ztarfile));
					exit(1);
				}
			}
			else
#endif
				tarfile = stdout;
			strcpy(filename, "-");
		}
		else
		{
#ifdef HAVE_LIBZ
			if (compresslevel != 0)
			{
				snprintf(filename, sizeof(filename), "%s/base.tar.gz", basedir);
				ztarfile = gzopen(filename, "wb");
				if (gzsetparams(ztarfile, compresslevel,
								Z_DEFAULT_STRATEGY) != Z_OK)
				{
					pg_log_error("could not set compression level %d: %s",
								 compresslevel, get_gz_error(ztarfile));
					exit(1);
				}
			}
			else
#endif
			{
				snprintf(filename, sizeof(filename), "%s/base.tar", basedir);
				tarfile = fopen(filename, "wb");
			}
		}
	}
	else
	{
		/*
		 * Specific tablespace
		 */
#ifdef HAVE_LIBZ
		if (compresslevel != 0)
		{
			snprintf(filename, sizeof(filename), "%s/%s.tar.gz", basedir,
					 PQgetvalue(res, rownum, 0));
			ztarfile = gzopen(filename, "wb");
			if (gzsetparams(ztarfile, compresslevel,
							Z_DEFAULT_STRATEGY) != Z_OK)
			{
				pg_log_error("could not set compression level %d: %s",
							 compresslevel, get_gz_error(ztarfile));
				exit(1);
			}
		}
		else
#endif
		{
			snprintf(filename, sizeof(filename), "%s/%s.tar", basedir,
					 PQgetvalue(res, rownum, 0));
			tarfile = fopen(filename, "wb");
		}
	}

#ifdef HAVE_LIBZ
	if (compresslevel != 0)
	{
		if (!ztarfile)
		{
			/* Compression is in use */
			pg_log_error("could not create compressed file \"%s\": %s",
						 filename, get_gz_error(ztarfile));
			exit(1);
		}
	}
	else
#endif
	{
		/* Either no zlib support, or zlib support but compresslevel = 0 */
		if (!tarfile)
		{
			pg_log_error("could not create file \"%s\": %m", filename);
			exit(1);
		}
	}

	/*
	 * Get the COPY data stream
	 */
	res = PQgetResult(conn);
	if (PQresultStatus(res) != PGRES_COPY_OUT)
	{
		pg_log_error("could not get COPY data stream: %s",
					 PQerrorMessage(conn));
		exit(1);
	}

	while (1)
	{
		int			r;

		if (copybuf != NULL)
		{
			PQfreemem(copybuf);
			copybuf = NULL;
		}

		r = PQgetCopyData(conn, &copybuf, 0);
		if (r == -1)
		{
			/*
			 * End of chunk. If requested, and this is the base tablespace,
			 * write configuration file into the tarfile. When done, close the
			 * file (but not stdout).
			 *
			 * Also, write two completely empty blocks at the end of the tar
			 * file, as required by some tar programs.
			 */
			char		zerobuf[1024];

			MemSet(zerobuf, 0, sizeof(zerobuf));

			if (basetablespace && writerecoveryconf)
			{
				char		header[512];

				/*
				 * If postgresql.auto.conf has not been found in the streamed
				 * data, add recovery configuration to postgresql.auto.conf if
				 * recovery parameters are GUCs.  If the instance connected to
				 * is older than 12, create recovery.conf with this data
				 * otherwise.
				 */
				if (!found_postgresql_auto_conf || !is_recovery_guc_supported)
				{
					int			padding;

					tarCreateHeader(header,
									is_recovery_guc_supported ? "postgresql.auto.conf" : "recovery.conf",
									NULL,
									recoveryconfcontents->len,
									pg_file_create_mode, 04000, 02000,
									time(NULL));

					padding = ((recoveryconfcontents->len + 511) & ~511) - recoveryconfcontents->len;

					WRITE_TAR_DATA(header, sizeof(header));
					WRITE_TAR_DATA(recoveryconfcontents->data,
								   recoveryconfcontents->len);
					if (padding)
						WRITE_TAR_DATA(zerobuf, padding);
				}

				/*
				 * standby.signal is supported only if recovery parameters are
				 * GUCs.
				 */
				if (is_recovery_guc_supported)
				{
					tarCreateHeader(header, "standby.signal", NULL,
									0,	/* zero-length file */
									pg_file_create_mode, 04000, 02000,
									time(NULL));

					WRITE_TAR_DATA(header, sizeof(header));
					WRITE_TAR_DATA(zerobuf, 511);
				}
			}

			/* 2 * 512 bytes empty data at end of file */
			WRITE_TAR_DATA(zerobuf, sizeof(zerobuf));

#ifdef HAVE_LIBZ
			if (ztarfile != NULL)
			{
				if (gzclose(ztarfile) != 0)
				{
					pg_log_error("could not close compressed file \"%s\": %s",
								 filename, get_gz_error(ztarfile));
					exit(1);
				}
			}
			else
#endif
			{
				if (strcmp(basedir, "-") != 0)
				{
					if (fclose(tarfile) != 0)
					{
						pg_log_error("could not close file \"%s\": %m",
									 filename);
						exit(1);
					}
				}
			}

			break;
		}
		else if (r == -2)
		{
			pg_log_error("could not read COPY data: %s",
						 PQerrorMessage(conn));
			exit(1);
		}

		if (!writerecoveryconf || !basetablespace)
		{
			/*
			 * When not writing config file, or when not working on the base
			 * tablespace, we never have to look for an existing configuration
			 * file in the stream.
			 */
			WRITE_TAR_DATA(copybuf, r);
		}
		else
		{
			/*
			 * Look for a config file in the existing tar stream. If it's
			 * there, we must skip it so we can later overwrite it with our
			 * own version of the file.
			 *
			 * To do this, we have to process the individual files inside the
			 * TAR stream. The stream consists of a header and zero or more
			 * chunks, all 512 bytes long. The stream from the server is
			 * broken up into smaller pieces, so we have to track the size of
			 * the files to find the next header structure.
			 */
			int			rr = r;
			int			pos = 0;

			while (rr > 0)
			{
				if (in_tarhdr)
				{
					/*
					 * We're currently reading a header structure inside the
					 * TAR stream, i.e. the file metadata.
					 */
					if (tarhdrsz < 512)
					{
						/*
						 * Copy the header structure into tarhdr in case the
						 * header is not aligned to 512 bytes or it's not
						 * returned in whole by the last PQgetCopyData call.
						 */
						int			hdrleft;
						int			bytes2copy;

						hdrleft = 512 - tarhdrsz;
						bytes2copy = (rr > hdrleft ? hdrleft : rr);

						memcpy(&tarhdr[tarhdrsz], copybuf + pos, bytes2copy);

						rr -= bytes2copy;
						pos += bytes2copy;
						tarhdrsz += bytes2copy;
					}
					else
					{
						/*
						 * We have the complete header structure in tarhdr,
						 * look at the file metadata: we may want append
						 * recovery info into postgresql.auto.conf and skip
						 * standby.signal file if recovery parameters are
						 * integrated as GUCs, and recovery.conf otherwise. In
						 * both cases we must calculate tar padding.
						 */
						if (is_recovery_guc_supported)
						{
							skip_file = (strcmp(&tarhdr[0], "standby.signal") == 0);
							is_postgresql_auto_conf = (strcmp(&tarhdr[0], "postgresql.auto.conf") == 0);
						}
						else
							skip_file = (strcmp(&tarhdr[0], "recovery.conf") == 0);

						filesz = read_tar_number(&tarhdr[124], 12);
						file_padding_len = ((filesz + 511) & ~511) - filesz;

						if (is_recovery_guc_supported &&
							is_postgresql_auto_conf &&
							writerecoveryconf)
						{
							/* replace tar header */
							char		header[512];

							tarCreateHeader(header, "postgresql.auto.conf", NULL,
											filesz + recoveryconfcontents->len,
											pg_file_create_mode, 04000, 02000,
											time(NULL));

							WRITE_TAR_DATA(header, sizeof(header));
						}
						else
						{
							/* copy stream with padding */
							filesz += file_padding_len;

							if (!skip_file)
							{
								/*
								 * If we're not skipping the file, write the
								 * tar header unmodified.
								 */
								WRITE_TAR_DATA(tarhdr, 512);
							}
						}

						/* Next part is the file, not the header */
						in_tarhdr = false;
					}
				}
				else
				{
					/*
					 * We're processing a file's contents.
					 */
					if (filesz > 0)
					{
						/*
						 * We still have data to read (and possibly write).
						 */
						int			bytes2write;

						bytes2write = (filesz > rr ? rr : filesz);

						if (!skip_file)
							WRITE_TAR_DATA(copybuf + pos, bytes2write);

						rr -= bytes2write;
						pos += bytes2write;
						filesz -= bytes2write;
					}
					else if (is_recovery_guc_supported &&
							 is_postgresql_auto_conf &&
							 writerecoveryconf)
					{
						/* append recovery config to postgresql.auto.conf */
						int			padding;
						int			tailsize;

						tailsize = (512 - file_padding_len) + recoveryconfcontents->len;
						padding = ((tailsize + 511) & ~511) - tailsize;

						WRITE_TAR_DATA(recoveryconfcontents->data, recoveryconfcontents->len);

						if (padding)
						{
							char		zerobuf[512];

							MemSet(zerobuf, 0, sizeof(zerobuf));
							WRITE_TAR_DATA(zerobuf, padding);
						}

						/* skip original file padding */
						is_postgresql_auto_conf = false;
						skip_file = true;
						filesz += file_padding_len;

						found_postgresql_auto_conf = true;
					}
					else
					{
						/*
						 * No more data in the current file, the next piece of
						 * data (if any) will be a new file header structure.
						 */
						in_tarhdr = true;
						skip_file = false;
						is_postgresql_auto_conf = false;
						tarhdrsz = 0;
						filesz = 0;
					}
				}
			}
		}
		totaldone += r;
		progress_report(rownum, filename, false);
	}							/* while (1) */
	progress_report(rownum, filename, true);

	if (copybuf != NULL)
		PQfreemem(copybuf);

	/*
	 * Do not sync the resulting tar file yet, all files are synced once at
	 * the end.
	 */
}