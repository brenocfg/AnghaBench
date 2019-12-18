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
struct TYPE_5__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  dir; int /*<<< orphan*/  file; } ;
struct TYPE_6__ {int kind; TYPE_1__ desc; } ;
typedef  TYPE_2__ AllocateDesc ;

/* Variables and functions */
#define  AllocateDescDir 131 
#define  AllocateDescFile 130 
#define  AllocateDescPipe 129 
#define  AllocateDescRawFD 128 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* allocatedDescs ; 
 int close (int /*<<< orphan*/ ) ; 
 int closedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int fclose (int /*<<< orphan*/ ) ; 
 size_t numAllocatedDescs ; 
 int pclose (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
FreeDesc(AllocateDesc *desc)
{
	int			result;

	/* Close the underlying object */
	switch (desc->kind)
	{
		case AllocateDescFile:
			result = fclose(desc->desc.file);
			break;
		case AllocateDescPipe:
			result = pclose(desc->desc.file);
			break;
		case AllocateDescDir:
			result = closedir(desc->desc.dir);
			break;
		case AllocateDescRawFD:
			result = close(desc->desc.fd);
			break;
		default:
			elog(ERROR, "AllocateDesc kind not recognized");
			result = 0;			/* keep compiler quiet */
			break;
	}

	/* Compact storage in the allocatedDescs array */
	numAllocatedDescs--;
	*desc = allocatedDescs[numAllocatedDescs];

	return result;
}