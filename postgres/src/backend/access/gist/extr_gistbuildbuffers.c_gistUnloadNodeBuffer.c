#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pfile; } ;
struct TYPE_6__ {int /*<<< orphan*/  pageBlocknum; int /*<<< orphan*/ * pageBuffer; } ;
typedef  TYPE_1__ GISTNodeBuffer ;
typedef  TYPE_2__ GISTBuildBuffers ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  WriteTempFileBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gistBuffersGetFreeBlock (TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gistUnloadNodeBuffer(GISTBuildBuffers *gfbb, GISTNodeBuffer *nodeBuffer)
{
	/* Check if we have something to write */
	if (nodeBuffer->pageBuffer)
	{
		BlockNumber blkno;

		/* Get free file block */
		blkno = gistBuffersGetFreeBlock(gfbb);

		/* Write block to the temporary file */
		WriteTempFileBlock(gfbb->pfile, blkno, nodeBuffer->pageBuffer);

		/* Free memory of that page */
		pfree(nodeBuffer->pageBuffer);
		nodeBuffer->pageBuffer = NULL;

		/* Save block number */
		nodeBuffer->pageBlocknum = blkno;
	}
}