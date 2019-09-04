#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int poll_needed; TYPE_1__* local; int /*<<< orphan*/ * poll_services; } ;
typedef  TYPE_2__ VCHIQ_STATE_T ;
struct TYPE_9__ {int localport; int /*<<< orphan*/  poll_flags; } ;
typedef  TYPE_3__ VCHIQ_SERVICE_T ;
struct TYPE_7__ {int /*<<< orphan*/  trigger; } ;

/* Variables and functions */
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_event_signal_local (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

inline void
request_poll(VCHIQ_STATE_T *state, VCHIQ_SERVICE_T *service, int poll_type)
{
	u32 value;

	if (service) {
		do {
			value = atomic_read(&service->poll_flags);
		} while (atomic_cmpxchg(&service->poll_flags, value,
			value | (1 << poll_type)) != value);

		do {
			value = atomic_read(&state->poll_services[
				service->localport>>5]);
		} while (atomic_cmpxchg(
			&state->poll_services[service->localport>>5],
			value, value | (1 << (service->localport & 0x1f)))
			!= value);
	}

	state->poll_needed = 1;
	wmb();

	/* ... and ensure the slot handler runs. */
	remote_event_signal_local(state, &state->local->trigger);
}