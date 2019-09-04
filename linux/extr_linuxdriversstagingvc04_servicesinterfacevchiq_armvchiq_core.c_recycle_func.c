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
struct TYPE_5__ {TYPE_2__* local; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_6__ {int /*<<< orphan*/  recycle; } ;
typedef  TYPE_2__ VCHIQ_SHARED_STATE_T ;
typedef  int /*<<< orphan*/  BITSET_T ;

/* Variables and functions */
 int BITSET_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VCHIQ_MAX_SERVICES ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_free_queue (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  remote_event_wait (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
recycle_func(void *v)
{
	VCHIQ_STATE_T *state = (VCHIQ_STATE_T *) v;
	VCHIQ_SHARED_STATE_T *local = state->local;
	BITSET_T *found;
	size_t length;

	length = sizeof(*found) * BITSET_SIZE(VCHIQ_MAX_SERVICES);

	found = kmalloc_array(BITSET_SIZE(VCHIQ_MAX_SERVICES), sizeof(*found),
			      GFP_KERNEL);
	if (!found)
		return -ENOMEM;

	while (1) {
		remote_event_wait(state, &local->recycle);

		process_free_queue(state, found, length);
	}
	return 0;
}