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
typedef  int TimeLineID ;

/* Variables and functions */
 int /*<<< orphan*/  KeepFileRestoredFromArchive (char*,char*) ; 
 int MAXFNAMELEN ; 
 int MAXPGPATH ; 
 scalar_t__ RestoreArchivedFile (char*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLHistoryFileName (char*,int) ; 

void
restoreTimeLineHistoryFiles(TimeLineID begin, TimeLineID end)
{
	char		path[MAXPGPATH];
	char		histfname[MAXFNAMELEN];
	TimeLineID	tli;

	for (tli = begin; tli < end; tli++)
	{
		if (tli == 1)
			continue;

		TLHistoryFileName(histfname, tli);
		if (RestoreArchivedFile(path, histfname, "RECOVERYHISTORY", 0, false))
			KeepFileRestoredFromArchive(path, histfname);
	}
}