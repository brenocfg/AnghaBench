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
struct TYPE_3__ {size_t nFreeBlocks; long* freeBlocks; int /*<<< orphan*/  nFileBlocks; } ;
typedef  TYPE_1__ GISTBuildBuffers ;

/* Variables and functions */

__attribute__((used)) static long
gistBuffersGetFreeBlock(GISTBuildBuffers *gfbb)
{
	/*
	 * If there are multiple free blocks, we select the one appearing last in
	 * freeBlocks[].  If there are none, assign the next block at the end of
	 * the file (causing the file to be extended).
	 */
	if (gfbb->nFreeBlocks > 0)
		return gfbb->freeBlocks[--gfbb->nFreeBlocks];
	else
		return gfbb->nFileBlocks++;
}