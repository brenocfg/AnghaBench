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
 int /*<<< orphan*/  BufferDescriptorGetContentLock (int /*<<< orphan*/ *) ; 
 scalar_t__ BufferIsLocal (scalar_t__) ; 
 int /*<<< orphan*/  BufferIsValid (scalar_t__) ; 
 int /*<<< orphan*/ * GetBufferDescriptor (scalar_t__) ; 
 int LWLockConditionalAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 

bool
ConditionalLockBuffer(Buffer buffer)
{
	BufferDesc *buf;

	Assert(BufferIsValid(buffer));
	if (BufferIsLocal(buffer))
		return true;			/* act as though we got it */

	buf = GetBufferDescriptor(buffer - 1);

	return LWLockConditionalAcquire(BufferDescriptorGetContentLock(buf),
									LW_EXCLUSIVE);
}