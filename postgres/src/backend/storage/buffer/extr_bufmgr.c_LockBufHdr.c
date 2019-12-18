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
typedef  int uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  SpinDelayStatus ;
typedef  TYPE_1__ BufferDesc ;

/* Variables and functions */
 int BM_LOCKED ; 
 int /*<<< orphan*/  finish_spin_delay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_local_spin_delay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perform_spin_delay (int /*<<< orphan*/ *) ; 
 int pg_atomic_fetch_or_u32 (int /*<<< orphan*/ *,int) ; 

uint32
LockBufHdr(BufferDesc *desc)
{
	SpinDelayStatus delayStatus;
	uint32		old_buf_state;

	init_local_spin_delay(&delayStatus);

	while (true)
	{
		/* set BM_LOCKED flag */
		old_buf_state = pg_atomic_fetch_or_u32(&desc->state, BM_LOCKED);
		/* if it wasn't set before we're OK */
		if (!(old_buf_state & BM_LOCKED))
			break;
		perform_spin_delay(&delayStatus);
	}
	finish_spin_delay(&delayStatus);
	return old_buf_state | BM_LOCKED;
}