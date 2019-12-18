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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int BUFFER_LOCK_EXCLUSIVE ; 
 int BUFFER_LOCK_SHARE ; 
 int BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferDescriptorGetContentLock (int /*<<< orphan*/ *) ; 
 scalar_t__ BufferIsLocal (scalar_t__) ; 
 int /*<<< orphan*/  BufferIsValid (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * GetBufferDescriptor (scalar_t__) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

void
LockBuffer(Buffer buffer, int mode)
{
	BufferDesc *buf;

	Assert(BufferIsValid(buffer));
	if (BufferIsLocal(buffer))
		return;					/* local buffers need no lock */

	buf = GetBufferDescriptor(buffer - 1);

	if (mode == BUFFER_LOCK_UNLOCK)
		LWLockRelease(BufferDescriptorGetContentLock(buf));
	else if (mode == BUFFER_LOCK_SHARE)
		LWLockAcquire(BufferDescriptorGetContentLock(buf), LW_SHARED);
	else if (mode == BUFFER_LOCK_EXCLUSIVE)
		LWLockAcquire(BufferDescriptorGetContentLock(buf), LW_EXCLUSIVE);
	else
		elog(ERROR, "unrecognized buffer lock mode: %d", mode);
}