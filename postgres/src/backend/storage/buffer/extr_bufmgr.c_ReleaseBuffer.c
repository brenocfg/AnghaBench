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
typedef  int Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferIsLocal (int) ; 
 int /*<<< orphan*/  BufferIsValid (int) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetBufferDescriptor (int) ; 
 scalar_t__* LocalRefCount ; 
 int /*<<< orphan*/  ResourceOwnerForgetBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnpinBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

void
ReleaseBuffer(Buffer buffer)
{
	if (!BufferIsValid(buffer))
		elog(ERROR, "bad buffer ID: %d", buffer);

	if (BufferIsLocal(buffer))
	{
		ResourceOwnerForgetBuffer(CurrentResourceOwner, buffer);

		Assert(LocalRefCount[-buffer - 1] > 0);
		LocalRefCount[-buffer - 1]--;
		return;
	}

	UnpinBuffer(GetBufferDescriptor(buffer - 1), true);
}