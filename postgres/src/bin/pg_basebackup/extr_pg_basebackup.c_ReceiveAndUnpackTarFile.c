#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int pgoff_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  current_path ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int MAXPGPATH ; 
 scalar_t__ PGRES_COPY_OUT ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int PQgetCopyData (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 int PQgetisnull (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteRecoveryConfig (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* basedir ; 
 scalar_t__ chmod (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 char* get_tablespace_mapping (char*) ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_dir_create_mode ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 scalar_t__ pg_str_endswith (char*,char*) ; 
 int /*<<< orphan*/  progress_report (int,char*,int) ; 
 int read_tar_number (char*,int) ; 
 int /*<<< orphan*/  recoveryconfcontents ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ symlink (char const*,char*) ; 
 int totaldone ; 
 scalar_t__ writerecoveryconf ; 

__attribute__((used)) static void
ReceiveAndUnpackTarFile(PGconn *conn, PGresult *res, int rownum)
{
	char		current_path[MAXPGPATH];
	char		filename[MAXPGPATH];
	const char *mapped_tblspc_path;
	pgoff_t		current_len_left = 0;
	int			current_padding = 0;
	bool		basetablespace;
	char	   *copybuf = NULL;
	FILE	   *file = NULL;

	basetablespace = PQgetisnull(res, rownum, 0);
	if (basetablespace)
		strlcpy(current_path, basedir, sizeof(current_path));
	else
		strlcpy(current_path,
				get_tablespace_mapping(PQgetvalue(res, rownum, 1)),
				sizeof(current_path));

	/*
	 * Get the COPY data
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
			 * End of chunk
			 */
			if (file)
				fclose(file);

			break;
		}
		else if (r == -2)
		{
			pg_log_error("could not read COPY data: %s",
						 PQerrorMessage(conn));
			exit(1);
		}

		if (file == NULL)
		{
#ifndef WIN32
			int			filemode;
#endif

			/*
			 * No current file, so this must be the header for a new file
			 */
			if (r != 512)
			{
				pg_log_error("invalid tar block header size: %d", r);
				exit(1);
			}
			totaldone += 512;

			current_len_left = read_tar_number(&copybuf[124], 12);

#ifndef WIN32
			/* Set permissions on the file */
			filemode = read_tar_number(&copybuf[100], 8);
#endif

			/*
			 * All files are padded up to 512 bytes
			 */
			current_padding =
				((current_len_left + 511) & ~511) - current_len_left;

			/*
			 * First part of header is zero terminated filename
			 */
			snprintf(filename, sizeof(filename), "%s/%s", current_path,
					 copybuf);
			if (filename[strlen(filename) - 1] == '/')
			{
				/*
				 * Ends in a slash means directory or symlink to directory
				 */
				if (copybuf[156] == '5')
				{
					/*
					 * Directory
					 */
					filename[strlen(filename) - 1] = '\0';	/* Remove trailing slash */
					if (mkdir(filename, pg_dir_create_mode) != 0)
					{
						/*
						 * When streaming WAL, pg_wal (or pg_xlog for pre-9.6
						 * clusters) will have been created by the wal
						 * receiver process. Also, when the WAL directory
						 * location was specified, pg_wal (or pg_xlog) has
						 * already been created as a symbolic link before
						 * starting the actual backup. So just ignore creation
						 * failures on related directories.
						 */
						if (!((pg_str_endswith(filename, "/pg_wal") ||
							   pg_str_endswith(filename, "/pg_xlog") ||
							   pg_str_endswith(filename, "/archive_status")) &&
							  errno == EEXIST))
						{
							pg_log_error("could not create directory \"%s\": %m",
										 filename);
							exit(1);
						}
					}
#ifndef WIN32
					if (chmod(filename, (mode_t) filemode))
						pg_log_error("could not set permissions on directory \"%s\": %m",
									 filename);
#endif
				}
				else if (copybuf[156] == '2')
				{
					/*
					 * Symbolic link
					 *
					 * It's most likely a link in pg_tblspc directory, to the
					 * location of a tablespace. Apply any tablespace mapping
					 * given on the command line (--tablespace-mapping). (We
					 * blindly apply the mapping without checking that the
					 * link really is inside pg_tblspc. We don't expect there
					 * to be other symlinks in a data directory, but if there
					 * are, you can call it an undocumented feature that you
					 * can map them too.)
					 */
					filename[strlen(filename) - 1] = '\0';	/* Remove trailing slash */

					mapped_tblspc_path = get_tablespace_mapping(&copybuf[157]);
					if (symlink(mapped_tblspc_path, filename) != 0)
					{
						pg_log_error("could not create symbolic link from \"%s\" to \"%s\": %m",
									 filename, mapped_tblspc_path);
						exit(1);
					}
				}
				else
				{
					pg_log_error("unrecognized link indicator \"%c\"",
								 copybuf[156]);
					exit(1);
				}
				continue;		/* directory or link handled */
			}

			/*
			 * regular file
			 */
			file = fopen(filename, "wb");
			if (!file)
			{
				pg_log_error("could not create file \"%s\": %m", filename);
				exit(1);
			}

#ifndef WIN32
			if (chmod(filename, (mode_t) filemode))
				pg_log_error("could not set permissions on file \"%s\": %m",
							 filename);
#endif

			if (current_len_left == 0)
			{
				/*
				 * Done with this file, next one will be a new tar header
				 */
				fclose(file);
				file = NULL;
				continue;
			}
		}						/* new file */
		else
		{
			/*
			 * Continuing blocks in existing file
			 */
			if (current_len_left == 0 && r == current_padding)
			{
				/*
				 * Received the padding block for this file, ignore it and
				 * close the file, then move on to the next tar header.
				 */
				fclose(file);
				file = NULL;
				totaldone += r;
				continue;
			}

			if (fwrite(copybuf, r, 1, file) != 1)
			{
				pg_log_error("could not write to file \"%s\": %m", filename);
				exit(1);
			}
			totaldone += r;
			progress_report(rownum, filename, false);

			current_len_left -= r;
			if (current_len_left == 0 && current_padding == 0)
			{
				/*
				 * Received the last block, and there is no padding to be
				 * expected. Close the file and move on to the next tar
				 * header.
				 */
				fclose(file);
				file = NULL;
				continue;
			}
		}						/* continuing data in existing file */
	}							/* loop over all data blocks */
	progress_report(rownum, filename, true);

	if (file != NULL)
	{
		pg_log_error("COPY stream ended before last file was finished");
		exit(1);
	}

	if (copybuf != NULL)
		PQfreemem(copybuf);

	if (basetablespace && writerecoveryconf)
		WriteRecoveryConfig(conn, basedir, recoveryconfcontents);

	/*
	 * No data is synced here, everything is done for all tablespaces at the
	 * end.
	 */
}