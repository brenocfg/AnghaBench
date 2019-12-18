#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ PrivateRefCountEntry ;
typedef  TYPE_2__ BufferDesc ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_LOCKED ; 
 scalar_t__ BUF_REFCOUNT_ONE ; 
 int /*<<< orphan*/  BufferDescriptorGetBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/ * GetPrivateRefCountEntry (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* NewPrivateRefCountEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceOwnerRememberBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_2__*,int) ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
PinBuffer_Locked(BufferDesc *buf)
{
	Buffer		b;
	PrivateRefCountEntry *ref;
	uint32		buf_state;

	/*
	 * As explained, We don't expect any preexisting pins. That allows us to
	 * manipulate the PrivateRefCount after releasing the spinlock
	 */
	Assert(GetPrivateRefCountEntry(BufferDescriptorGetBuffer(buf), false) == NULL);

	/*
	 * Since we hold the buffer spinlock, we can update the buffer state and
	 * release the lock in one operation.
	 */
	buf_state = pg_atomic_read_u32(&buf->state);
	Assert(buf_state & BM_LOCKED);
	buf_state += BUF_REFCOUNT_ONE;
	UnlockBufHdr(buf, buf_state);

	b = BufferDescriptorGetBuffer(buf);

	ref = NewPrivateRefCountEntry(b);
	ref->refcount++;

	ResourceOwnerRememberBuffer(CurrentResourceOwner, b);
}