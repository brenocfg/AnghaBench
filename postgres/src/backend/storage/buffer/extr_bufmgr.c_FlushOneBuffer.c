#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BufferDesc ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferDescriptorGetContentLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BufferIsLocal (scalar_t__) ; 
 int BufferIsPinned (scalar_t__) ; 
 int /*<<< orphan*/  FlushBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetBufferDescriptor (scalar_t__) ; 
 int LWLockHeldByMe (int /*<<< orphan*/ ) ; 

void
FlushOneBuffer(Buffer buffer)
{
	BufferDesc *bufHdr;

	/* currently not needed, but no fundamental reason not to support */
	Assert(!BufferIsLocal(buffer));

	Assert(BufferIsPinned(buffer));

	bufHdr = GetBufferDescriptor(buffer - 1);

	Assert(LWLockHeldByMe(BufferDescriptorGetContentLock(bufHdr)));

	FlushBuffer(bufHdr, NULL);
}