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
struct TYPE_5__ {int /*<<< orphan*/  blockNum; } ;
struct TYPE_6__ {TYPE_1__ tag; } ;
typedef  TYPE_2__ BufferDesc ;
typedef  int Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsLocal (int) ; 
 int /*<<< orphan*/  BufferIsPinned (int) ; 
 TYPE_2__* GetBufferDescriptor (int) ; 
 TYPE_2__* GetLocalBufferDescriptor (int) ; 

BlockNumber
BufferGetBlockNumber(Buffer buffer)
{
	BufferDesc *bufHdr;

	Assert(BufferIsPinned(buffer));

	if (BufferIsLocal(buffer))
		bufHdr = GetLocalBufferDescriptor(-buffer - 1);
	else
		bufHdr = GetBufferDescriptor(buffer - 1);

	/* pinned, so OK to read tag without spinlock */
	return bufHdr->tag.blockNum;
}