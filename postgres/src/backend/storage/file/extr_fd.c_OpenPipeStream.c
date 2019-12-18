#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * file; } ;
struct TYPE_5__ {TYPE_1__ desc; int /*<<< orphan*/  create_subid; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ AllocateDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateDescPipe ; 
 int /*<<< orphan*/  DO_DB (int /*<<< orphan*/ ) ; 
 int EMFILE ; 
 int ENFILE ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ ReleaseLruFile () ; 
 int /*<<< orphan*/  ReleaseLruFiles () ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 TYPE_2__* allocatedDescs ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maxAllocatedDescs ; 
 size_t numAllocatedDescs ; 
 int /*<<< orphan*/ * popen (char const*,char const*) ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserveAllocatedDesc () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

FILE *
OpenPipeStream(const char *command, const char *mode)
{
	FILE	   *file;
	int			save_errno;

	DO_DB(elog(LOG, "OpenPipeStream: Allocated %d (%s)",
			   numAllocatedDescs, command));

	/* Can we allocate another non-virtual FD? */
	if (!reserveAllocatedDesc())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_RESOURCES),
				 errmsg("exceeded maxAllocatedDescs (%d) while trying to execute command \"%s\"",
						maxAllocatedDescs, command)));

	/* Close excess kernel FDs. */
	ReleaseLruFiles();

TryAgain:
	fflush(stdout);
	fflush(stderr);
	pqsignal(SIGPIPE, SIG_DFL);
	errno = 0;
	file = popen(command, mode);
	save_errno = errno;
	pqsignal(SIGPIPE, SIG_IGN);
	errno = save_errno;
	if (file != NULL)
	{
		AllocateDesc *desc = &allocatedDescs[numAllocatedDescs];

		desc->kind = AllocateDescPipe;
		desc->desc.file = file;
		desc->create_subid = GetCurrentSubTransactionId();
		numAllocatedDescs++;
		return desc->desc.file;
	}

	if (errno == EMFILE || errno == ENFILE)
	{
		ereport(LOG,
				(errcode(ERRCODE_INSUFFICIENT_RESOURCES),
				 errmsg("out of file descriptors: %m; release and retry")));
		if (ReleaseLruFile())
			goto TryAgain;
		errno = save_errno;
	}

	return NULL;
}