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
struct TYPE_4__ {int /*<<< orphan*/ * dir; } ;
struct TYPE_5__ {TYPE_1__ desc; int /*<<< orphan*/  create_subid; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  DIR ;
typedef  TYPE_2__ AllocateDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateDescDir ; 
 int /*<<< orphan*/  DO_DB (int /*<<< orphan*/ ) ; 
 int EMFILE ; 
 int ENFILE ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ ReleaseLruFile () ; 
 int /*<<< orphan*/  ReleaseLruFiles () ; 
 TYPE_2__* allocatedDescs ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  maxAllocatedDescs ; 
 size_t numAllocatedDescs ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  reserveAllocatedDesc () ; 

DIR *
AllocateDir(const char *dirname)
{
	DIR		   *dir;

	DO_DB(elog(LOG, "AllocateDir: Allocated %d (%s)",
			   numAllocatedDescs, dirname));

	/* Can we allocate another non-virtual FD? */
	if (!reserveAllocatedDesc())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_RESOURCES),
				 errmsg("exceeded maxAllocatedDescs (%d) while trying to open directory \"%s\"",
						maxAllocatedDescs, dirname)));

	/* Close excess kernel FDs. */
	ReleaseLruFiles();

TryAgain:
	if ((dir = opendir(dirname)) != NULL)
	{
		AllocateDesc *desc = &allocatedDescs[numAllocatedDescs];

		desc->kind = AllocateDescDir;
		desc->desc.dir = dir;
		desc->create_subid = GetCurrentSubTransactionId();
		numAllocatedDescs++;
		return desc->desc.dir;
	}

	if (errno == EMFILE || errno == ENFILE)
	{
		int			save_errno = errno;

		ereport(LOG,
				(errcode(ERRCODE_INSUFFICIENT_RESOURCES),
				 errmsg("out of file descriptors: %m; release and retry")));
		errno = 0;
		if (ReleaseLruFile())
			goto TryAgain;
		errno = save_errno;
	}

	return NULL;
}