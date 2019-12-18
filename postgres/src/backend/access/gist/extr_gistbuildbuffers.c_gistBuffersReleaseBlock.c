#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nFreeBlocks; int freeBlocksLen; long* freeBlocks; } ;
typedef  TYPE_1__ GISTBuildBuffers ;

/* Variables and functions */
 scalar_t__ repalloc (long*,int) ; 

__attribute__((used)) static void
gistBuffersReleaseBlock(GISTBuildBuffers *gfbb, long blocknum)
{
	int			ndx;

	/* Enlarge freeBlocks array if full. */
	if (gfbb->nFreeBlocks >= gfbb->freeBlocksLen)
	{
		gfbb->freeBlocksLen *= 2;
		gfbb->freeBlocks = (long *) repalloc(gfbb->freeBlocks,
											 gfbb->freeBlocksLen *
											 sizeof(long));
	}

	/* Add blocknum to array */
	ndx = gfbb->nFreeBlocks++;
	gfbb->freeBlocks[ndx] = blocknum;
}