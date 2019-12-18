#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  scalar_t__ uint32 ;
typedef  void* XLogRecPtr ;
typedef  scalar_t__ TimeLineID ;
struct TYPE_6__ {int end; void* begin; scalar_t__ tli; } ;
typedef  TYPE_1__ TimeLineHistoryEntry ;

/* Variables and functions */
 void* InvalidXLogRecPtr ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 TYPE_1__* pg_malloc (int) ; 
 TYPE_1__* pg_realloc (TYPE_1__*,int) ; 
 int sscanf (char*,char*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

TimeLineHistoryEntry *
rewind_parseTimeLineHistory(char *buffer, TimeLineID targetTLI, int *nentries)
{
	char	   *fline;
	TimeLineHistoryEntry *entry;
	TimeLineHistoryEntry *entries = NULL;
	int			nlines = 0;
	TimeLineID	lasttli = 0;
	XLogRecPtr	prevend;
	char	   *bufptr;
	bool		lastline = false;

	/*
	 * Parse the file...
	 */
	prevend = InvalidXLogRecPtr;
	bufptr = buffer;
	while (!lastline)
	{
		char	   *ptr;
		TimeLineID	tli;
		uint32		switchpoint_hi;
		uint32		switchpoint_lo;
		int			nfields;

		fline = bufptr;
		while (*bufptr && *bufptr != '\n')
			bufptr++;
		if (!(*bufptr))
			lastline = true;
		else
			*bufptr++ = '\0';

		/* skip leading whitespace and check for # comment */
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
			pg_log_error("syntax error in history file: %s", fline);
			pg_log_error("Expected a numeric timeline ID.");
			exit(1);
		}
		if (nfields != 3)
		{
			pg_log_error("syntax error in history file: %s", fline);
			pg_log_error("Expected a write-ahead log switchpoint location.");
			exit(1);
		}
		if (entries && tli <= lasttli)
		{
			pg_log_error("invalid data in history file: %s", fline);
			pg_log_error("Timeline IDs must be in increasing sequence.");
			exit(1);
		}

		lasttli = tli;

		nlines++;
		entries = pg_realloc(entries, nlines * sizeof(TimeLineHistoryEntry));

		entry = &entries[nlines - 1];
		entry->tli = tli;
		entry->begin = prevend;
		entry->end = ((uint64) (switchpoint_hi)) << 32 | (uint64) switchpoint_lo;
		prevend = entry->end;

		/* we ignore the remainder of each line */
	}

	if (entries && targetTLI <= lasttli)
	{
		pg_log_error("invalid data in history file");
		pg_log_error("Timeline IDs must be less than child timeline's ID.");
		exit(1);
	}

	/*
	 * Create one more entry for the "tip" of the timeline, which has no entry
	 * in the history file.
	 */
	nlines++;
	if (entries)
		entries = pg_realloc(entries, nlines * sizeof(TimeLineHistoryEntry));
	else
		entries = pg_malloc(1 * sizeof(TimeLineHistoryEntry));

	entry = &entries[nlines - 1];
	entry->tli = targetTLI;
	entry->begin = prevend;
	entry->end = InvalidXLogRecPtr;

	*nentries = nlines;
	return entries;
}