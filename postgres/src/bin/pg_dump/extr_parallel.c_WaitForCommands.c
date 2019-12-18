#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  TocEntry ;
typedef  scalar_t__ T_Action ;
struct TYPE_8__ {int (* WorkerJobDumpPtr ) (TYPE_1__*,int /*<<< orphan*/ *) ;int (* WorkerJobRestorePtr ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ ACT_DUMP ; 
 scalar_t__ ACT_RESTORE ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  buildWorkerResponse (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getMessageFromMaster (int*) ; 
 int /*<<< orphan*/  lockTableForWorker (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parseWorkerCommand (TYPE_1__*,int /*<<< orphan*/ **,scalar_t__*,char*) ; 
 int /*<<< orphan*/  sendMessageToMaster (int*,char*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
WaitForCommands(ArchiveHandle *AH, int pipefd[2])
{
	char	   *command;
	TocEntry   *te;
	T_Action	act;
	int			status = 0;
	char		buf[256];

	for (;;)
	{
		if (!(command = getMessageFromMaster(pipefd)))
		{
			/* EOF, so done */
			return;
		}

		/* Decode the command */
		parseWorkerCommand(AH, &te, &act, command);

		if (act == ACT_DUMP)
		{
			/* Acquire lock on this table within the worker's session */
			lockTableForWorker(AH, te);

			/* Perform the dump command */
			status = (AH->WorkerJobDumpPtr) (AH, te);
		}
		else if (act == ACT_RESTORE)
		{
			/* Perform the restore command */
			status = (AH->WorkerJobRestorePtr) (AH, te);
		}
		else
			Assert(false);

		/* Return status to master */
		buildWorkerResponse(AH, te, act, status, buf, sizeof(buf));

		sendMessageToMaster(pipefd, buf);

		/* command was pg_malloc'd and we are responsible for free()ing it. */
		free(command);
	}
}