#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fd; } ;
struct TYPE_6__ {scalar_t__ kind; TYPE_1__ desc; } ;
typedef  TYPE_2__ AllocateDesc ;

/* Variables and functions */
 scalar_t__ AllocateDescRawFD ; 
 int /*<<< orphan*/  DO_DB (int /*<<< orphan*/ ) ; 
 int FreeDesc (TYPE_2__*) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  WARNING ; 
 TYPE_2__* allocatedDescs ; 
 int close (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int numAllocatedDescs ; 

int
CloseTransientFile(int fd)
{
	int			i;

	DO_DB(elog(LOG, "CloseTransientFile: Allocated %d", numAllocatedDescs));

	/* Remove fd from list of allocated files, if it's present */
	for (i = numAllocatedDescs; --i >= 0;)
	{
		AllocateDesc *desc = &allocatedDescs[i];

		if (desc->kind == AllocateDescRawFD && desc->desc.fd == fd)
			return FreeDesc(desc);
	}

	/* Only get here if someone passes us a file not in allocatedDescs */
	elog(WARNING, "fd passed to CloseTransientFile was not obtained from OpenTransientFile");

	return close(fd);
}