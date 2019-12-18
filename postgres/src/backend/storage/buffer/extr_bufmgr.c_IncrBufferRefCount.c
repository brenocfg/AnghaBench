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
struct TYPE_3__ {int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ PrivateRefCountEntry ;
typedef  int Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsLocal (int) ; 
 int /*<<< orphan*/  BufferIsPinned (int) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 TYPE_1__* GetPrivateRefCountEntry (int,int) ; 
 int /*<<< orphan*/ * LocalRefCount ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceOwnerRememberBuffer (int /*<<< orphan*/ ,int) ; 

void
IncrBufferRefCount(Buffer buffer)
{
	Assert(BufferIsPinned(buffer));
	ResourceOwnerEnlargeBuffers(CurrentResourceOwner);
	if (BufferIsLocal(buffer))
		LocalRefCount[-buffer - 1]++;
	else
	{
		PrivateRefCountEntry *ref;

		ref = GetPrivateRefCountEntry(buffer, true);
		Assert(ref != NULL);
		ref->refcount++;
	}
	ResourceOwnerRememberBuffer(CurrentResourceOwner, buffer);
}