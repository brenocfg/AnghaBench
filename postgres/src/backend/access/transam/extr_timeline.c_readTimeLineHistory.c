#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  fline ;
typedef  void* XLogRecPtr ;
typedef  int TimeLineID ;
struct TYPE_4__ {int tli; int begin; int end; } ;
typedef  TYPE_1__ TimeLineHistoryEntry ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char*,char*) ; 
 scalar_t__ ArchiveRecoveryRequested ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 void* InvalidXLogRecPtr ; 
 int /*<<< orphan*/  KeepFileRestoredFromArchive (char*,char*) ; 
 int MAXFNAMELEN ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/ * NIL ; 
 int RestoreArchivedFile (char*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLHistoryFileName (char*,int) ; 
 int /*<<< orphan*/  TLHistoryFilePath (char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/ * lcons (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make1 (TYPE_1__*) ; 
 scalar_t__ palloc (int) ; 
 int sscanf (char*,char*,int*,scalar_t__*,scalar_t__*) ; 

List *
readTimeLineHistory(TimeLineID targetTLI)
{
	List	   *result;
	char		path[MAXPGPATH];
	char		histfname[MAXFNAMELEN];
	char		fline[MAXPGPATH];
	FILE	   *fd;
	TimeLineHistoryEntry *entry;
	TimeLineID	lasttli = 0;
	XLogRecPtr	prevend;
	bool		fromArchive = false;

	/* Timeline 1 does not have a history file, so no need to check */
	if (targetTLI == 1)
	{
		entry = (TimeLineHistoryEntry *) palloc(sizeof(TimeLineHistoryEntry));
		entry->tli = targetTLI;
		entry->begin = entry->end = InvalidXLogRecPtr;
		return list_make1(entry);
	}

	if (ArchiveRecoveryRequested)
	{
		TLHistoryFileName(histfname, targetTLI);
		fromArchive =
			RestoreArchivedFile(path, histfname, "RECOVERYHISTORY", 0, false);
	}
	else
		TLHistoryFilePath(path, targetTLI);

	fd = AllocateFile(path, "r");
	if (fd == NULL)
	{
		if (errno != ENOENT)
			ereport(FATAL,
					(errcode_for_file_access(),
					 errmsg("could not open file \"%s\": %m", path)));
		/* Not there, so assume no parents */
		entry = (TimeLineHistoryEntry *) palloc(sizeof(TimeLineHistoryEntry));
		entry->tli = targetTLI;
		entry->begin = entry->end = InvalidXLogRecPtr;
		return list_make1(entry);
	}

	result = NIL;

	/*
	 * Parse the file...
	 */
	prevend = InvalidXLogRecPtr;
	while (fgets(fline, sizeof(fline), fd) != NULL)
	{
		/* skip leading whitespace and check for # comment */
		char	   *ptr;
		TimeLineID	tli;
		uint32		switchpoint_hi;
		uint32		switchpoint_lo;
		int			nfields;

		for (ptr = fline; *ptr; ptr++)
		{
			if (!isspace((unsigned char) *ptr))
				break;
		}
		if (*ptr == '\0' || *ptr == '#')
			continue;

		nfields = sscanf(fline, "%u\t%X/%X", &tli, &switchpoint_hi, &switchpoint_lo);

		if (nfields < 1)
		{
			/* expect a numeric timeline ID as first field of line */
			ereport(FATAL,
					(errmsg("syntax error in history file: %s", fline),
					 errhint("Expected a numeric timeline ID.")));
		}
		if (nfields != 3)
			ereport(FATAL,
					(errmsg("syntax error in history file: %s", fline),
					 errhint("Expected a write-ahead log switchpoint location.")));

		if (result && tli <= lasttli)
			ereport(FATAL,
					(errmsg("invalid data in history file: %s", fline),
					 errhint("Timeline IDs must be in increasing sequence.")));

		lasttli = tli;

		entry = (TimeLineHistoryEntry *) palloc(sizeof(TimeLineHistoryEntry));
		entry->tli = tli;
		entry->begin = prevend;
		entry->end = ((uint64) (switchpoint_hi)) << 32 | (uint64) switchpoint_lo;
		prevend = entry->end;

		/* Build list with newest item first */
		result = lcons(entry, result);

		/* we ignore the remainder of each line */
	}

	FreeFile(fd);

	if (result && targetTLI <= lasttli)
		ereport(FATAL,
				(errmsg("invalid data in history file \"%s\"", path),
				 errhint("Timeline IDs must be less than child timeline's ID.")));

	/*
	 * Create one more entry for the "tip" of the timeline, which has no entry
	 * in the history file.
	 */
	entry = (TimeLineHistoryEntry *) palloc(sizeof(TimeLineHistoryEntry));
	entry->tli = targetTLI;
	entry->begin = prevend;
	entry->end = InvalidXLogRecPtr;

	result = lcons(entry, result);

	/*
	 * If the history file was fetched from archive, save it in pg_wal for
	 * future reference.
	 */
	if (fromArchive)
		KeepFileRestoredFromArchive(path, histfname);

	return result;
}