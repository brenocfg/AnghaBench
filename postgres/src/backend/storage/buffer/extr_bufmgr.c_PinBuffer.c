#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;
struct TYPE_8__ {scalar_t__ refcount; } ;
typedef  TYPE_1__ PrivateRefCountEntry ;
typedef  TYPE_2__ BufferDesc ;
typedef  int /*<<< orphan*/ * BufferAccessStrategy ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_LOCKED ; 
 scalar_t__ BM_MAX_USAGE_COUNT ; 
 int BM_VALID ; 
 scalar_t__ BUF_REFCOUNT_ONE ; 
 scalar_t__ BUF_STATE_GET_USAGECOUNT (int) ; 
 scalar_t__ BUF_USAGECOUNT_ONE ; 
 int /*<<< orphan*/  BufferDescriptorGetBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 TYPE_1__* GetPrivateRefCountEntry (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* NewPrivateRefCountEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReservePrivateRefCountEntry () ; 
 int /*<<< orphan*/  ResourceOwnerRememberBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WaitBufHdrUnlocked (TYPE_2__*) ; 
 scalar_t__ pg_atomic_compare_exchange_u32 (int /*<<< orphan*/ *,int*,int) ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
PinBuffer(BufferDesc *buf, BufferAccessStrategy strategy)
{
	Buffer		b = BufferDescriptorGetBuffer(buf);
	bool		result;
	PrivateRefCountEntry *ref;

	ref = GetPrivateRefCountEntry(b, true);

	if (ref == NULL)
	{
		uint32		buf_state;
		uint32		old_buf_state;

		ReservePrivateRefCountEntry();
		ref = NewPrivateRefCountEntry(b);

		old_buf_state = pg_atomic_read_u32(&buf->state);
		for (;;)
		{
			if (old_buf_state & BM_LOCKED)
				old_buf_state = WaitBufHdrUnlocked(buf);

			buf_state = old_buf_state;

			/* increase refcount */
			buf_state += BUF_REFCOUNT_ONE;

			if (strategy == NULL)
			{
				/* Default case: increase usagecount unless already max. */
				if (BUF_STATE_GET_USAGECOUNT(buf_state) < BM_MAX_USAGE_COUNT)
					buf_state += BUF_USAGECOUNT_ONE;
			}
			else
			{
				/*
				 * Ring buffers shouldn't evict others from pool.  Thus we
				 * don't make usagecount more than 1.
				 */
				if (BUF_STATE_GET_USAGECOUNT(buf_state) == 0)
					buf_state += BUF_USAGECOUNT_ONE;
			}

			if (pg_atomic_compare_exchange_u32(&buf->state, &old_buf_state,
											   buf_state))
			{
				result = (buf_state & BM_VALID) != 0;
				break;
			}
		}
	}
	else
	{
		/* If we previously pinned the buffer, it must surely be valid */
		result = true;
	}

	ref->refcount++;
	Assert(ref->refcount > 0);
	ResourceOwnerRememberBuffer(CurrentResourceOwner, b);
	return result;
}