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
typedef  int /*<<< orphan*/  TocEntry ;
typedef  int /*<<< orphan*/  T_Action ;
typedef  int /*<<< orphan*/  DumpId ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ACT_DUMP ; 
 int /*<<< orphan*/  ACT_RESTORE ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/ * getTocEntryByDumpId (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ messageStartsWith (char const*,char*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int /*<<< orphan*/ *,int*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
parseWorkerCommand(ArchiveHandle *AH, TocEntry **te, T_Action *act,
				   const char *msg)
{
	DumpId		dumpId;
	int			nBytes;

	if (messageStartsWith(msg, "DUMP "))
	{
		*act = ACT_DUMP;
		sscanf(msg, "DUMP %d%n", &dumpId, &nBytes);
		Assert(nBytes == strlen(msg));
		*te = getTocEntryByDumpId(AH, dumpId);
		Assert(*te != NULL);
	}
	else if (messageStartsWith(msg, "RESTORE "))
	{
		*act = ACT_RESTORE;
		sscanf(msg, "RESTORE %d%n", &dumpId, &nBytes);
		Assert(nBytes == strlen(msg));
		*te = getTocEntryByDumpId(AH, dumpId);
		Assert(*te != NULL);
	}
	else
		fatal("unrecognized command received from master: \"%s\"",
			  msg);
}