#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int TimeLineID ;
struct TYPE_10__ {int tli; int begin; int end; } ;
typedef  TYPE_2__ TimeLineHistoryEntry ;
struct TYPE_9__ {int ThisTimeLineID; } ;
struct TYPE_11__ {TYPE_1__ checkPointCopy; } ;
typedef  TYPE_3__ ControlFileData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_3__ ControlFile_source ; 
 TYPE_3__ ControlFile_target ; 
 int InvalidXLogRecPtr ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  TLHistoryFilePath (char*,int) ; 
 int /*<<< orphan*/  datadir_target ; 
 scalar_t__ debug ; 
 char* fetchFile (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_fatal (char*) ; 
 int /*<<< orphan*/  pg_free (char*) ; 
 int /*<<< orphan*/  pg_log_debug (char*,...) ; 
 scalar_t__ pg_malloc (int) ; 
 TYPE_2__* rewind_parseTimeLineHistory (char*,int,int*) ; 
 char* slurpFile (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int targetNentries ; 

__attribute__((used)) static TimeLineHistoryEntry *
getTimelineHistory(ControlFileData *controlFile, int *nentries)
{
	TimeLineHistoryEntry *history;
	TimeLineID	tli;

	tli = controlFile->checkPointCopy.ThisTimeLineID;

	/*
	 * Timeline 1 does not have a history file, so there is no need to check
	 * and fake an entry with infinite start and end positions.
	 */
	if (tli == 1)
	{
		history = (TimeLineHistoryEntry *) pg_malloc(sizeof(TimeLineHistoryEntry));
		history->tli = tli;
		history->begin = history->end = InvalidXLogRecPtr;
		*nentries = 1;
	}
	else
	{
		char		path[MAXPGPATH];
		char	   *histfile;

		TLHistoryFilePath(path, tli);

		/* Get history file from appropriate source */
		if (controlFile == &ControlFile_source)
			histfile = fetchFile(path, NULL);
		else if (controlFile == &ControlFile_target)
			histfile = slurpFile(datadir_target, path, NULL);
		else
			pg_fatal("invalid control file");

		history = rewind_parseTimeLineHistory(histfile, tli, nentries);
		pg_free(histfile);
	}

	if (debug)
	{
		int			i;

		if (controlFile == &ControlFile_source)
			pg_log_debug("Source timeline history:");
		else if (controlFile == &ControlFile_target)
			pg_log_debug("Target timeline history:");
		else
			Assert(false);

		/*
		 * Print the target timeline history.
		 */
		for (i = 0; i < targetNentries; i++)
		{
			TimeLineHistoryEntry *entry;

			entry = &history[i];
			pg_log_debug("%d: %X/%X - %X/%X", entry->tli,
						 (uint32) (entry->begin >> 32), (uint32) (entry->begin),
						 (uint32) (entry->end >> 32), (uint32) (entry->end));
		}
	}

	return history;
}