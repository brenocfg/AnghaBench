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
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ BufferDesc ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int BM_PERMANENT ; 
 scalar_t__ BufferIsLocal (scalar_t__) ; 
 int /*<<< orphan*/  BufferIsPinned (scalar_t__) ; 
 int /*<<< orphan*/  BufferIsValid (scalar_t__) ; 
 TYPE_1__* GetBufferDescriptor (scalar_t__) ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 

bool
BufferIsPermanent(Buffer buffer)
{
	BufferDesc *bufHdr;

	/* Local buffers are used only for temp relations. */
	if (BufferIsLocal(buffer))
		return false;

	/* Make sure we've got a real buffer, and that we hold a pin on it. */
	Assert(BufferIsValid(buffer));
	Assert(BufferIsPinned(buffer));

	/*
	 * BM_PERMANENT can't be changed while we hold a pin on the buffer, so we
	 * need not bother with the buffer header spinlock.  Even if someone else
	 * changes the buffer header state while we're doing this, the state is
	 * changed atomically, so we'll read the old value or the new value, but
	 * not random garbage.
	 */
	bufHdr = GetBufferDescriptor(buffer - 1);
	return (pg_atomic_read_u32(&bufHdr->state) & BM_PERMANENT) != 0;
}