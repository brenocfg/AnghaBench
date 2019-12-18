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
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_4__ {int fd; } ;
struct TYPE_5__ {int /*<<< orphan*/  create_subid; TYPE_1__ desc; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ AllocateDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateDescRawFD ; 
 int BasicOpenFilePerm (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_DB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  ReleaseLruFiles () ; 
 TYPE_2__* allocatedDescs ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  maxAllocatedDescs ; 
 size_t numAllocatedDescs ; 
 int /*<<< orphan*/  reserveAllocatedDesc () ; 

int
OpenTransientFilePerm(const char *fileName, int fileFlags, mode_t fileMode)
{
	int			fd;

	DO_DB(elog(LOG, "OpenTransientFile: Allocated %d (%s)",
			   numAllocatedDescs, fileName));

	/* Can we allocate another non-virtual FD? */
	if (!reserveAllocatedDesc())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_RESOURCES),
				 errmsg("exceeded maxAllocatedDescs (%d) while trying to open file \"%s\"",
						maxAllocatedDescs, fileName)));

	/* Close excess kernel FDs. */
	ReleaseLruFiles();

	fd = BasicOpenFilePerm(fileName, fileFlags, fileMode);

	if (fd >= 0)
	{
		AllocateDesc *desc = &allocatedDescs[numAllocatedDescs];

		desc->kind = AllocateDescRawFD;
		desc->desc.fd = fd;
		desc->create_subid = GetCurrentSubTransactionId();
		numAllocatedDescs++;

		return fd;
	}

	return -1;					/* failure */
}