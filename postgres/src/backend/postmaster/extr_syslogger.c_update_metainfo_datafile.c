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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG ; 
 int LOG_DESTINATION_CSVLOG ; 
 int LOG_DESTINATION_STDERR ; 
 int /*<<< orphan*/  LOG_METAINFO_DATAFILE ; 
 int /*<<< orphan*/  LOG_METAINFO_DATAFILE_TMP ; 
 int Log_destination ; 
 int /*<<< orphan*/  PG_IOLBF ; 
 int /*<<< orphan*/  _O_TEXT ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* last_csv_file_name ; 
 char* last_file_name ; 
 int /*<<< orphan*/  pg_mode_mask ; 
 scalar_t__ rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_metainfo_datafile(void)
{
	FILE	   *fh;
	mode_t		oumask;

	if (!(Log_destination & LOG_DESTINATION_STDERR) &&
		!(Log_destination & LOG_DESTINATION_CSVLOG))
	{
		if (unlink(LOG_METAINFO_DATAFILE) < 0 && errno != ENOENT)
			ereport(LOG,
					(errcode_for_file_access(),
					 errmsg("could not remove file \"%s\": %m",
							LOG_METAINFO_DATAFILE)));
		return;
	}

	/* use the same permissions as the data directory for the new file */
	oumask = umask(pg_mode_mask);
	fh = fopen(LOG_METAINFO_DATAFILE_TMP, "w");
	umask(oumask);

	if (fh)
	{
		setvbuf(fh, NULL, PG_IOLBF, 0);

#ifdef WIN32
		/* use CRLF line endings on Windows */
		_setmode(_fileno(fh), _O_TEXT);
#endif
	}
	else
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\": %m",
						LOG_METAINFO_DATAFILE_TMP)));
		return;
	}

	if (last_file_name && (Log_destination & LOG_DESTINATION_STDERR))
	{
		if (fprintf(fh, "stderr %s\n", last_file_name) < 0)
		{
			ereport(LOG,
					(errcode_for_file_access(),
					 errmsg("could not write file \"%s\": %m",
							LOG_METAINFO_DATAFILE_TMP)));
			fclose(fh);
			return;
		}
	}

	if (last_csv_file_name && (Log_destination & LOG_DESTINATION_CSVLOG))
	{
		if (fprintf(fh, "csvlog %s\n", last_csv_file_name) < 0)
		{
			ereport(LOG,
					(errcode_for_file_access(),
					 errmsg("could not write file \"%s\": %m",
							LOG_METAINFO_DATAFILE_TMP)));
			fclose(fh);
			return;
		}
	}
	fclose(fh);

	if (rename(LOG_METAINFO_DATAFILE_TMP, LOG_METAINFO_DATAFILE) != 0)
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not rename file \"%s\" to \"%s\": %m",
						LOG_METAINFO_DATAFILE_TMP, LOG_METAINFO_DATAFILE)));
}