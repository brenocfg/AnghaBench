#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dim_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dim_is_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_ERR_DRIVER_NOT_INITIALIZED ; 
 int channel_service_interrupt (struct dim_channel* const) ; 
 int /*<<< orphan*/  dim_on_error (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ g ; 

void dim_service_ahb_int_irq(struct dim_channel *const *channels)
{
	bool state_changed;

	if (!g.dim_is_initialized) {
		dim_on_error(DIM_ERR_DRIVER_NOT_INITIALIZED,
			     "DIM is not initialized");
		return;
	}

	if (!channels) {
		dim_on_error(DIM_ERR_DRIVER_NOT_INITIALIZED, "Bad channels");
		return;
	}

	/*
	 * Use while-loop and a flag to make sure the age is changed back at
	 * least once, otherwise the interrupt may never come if CPU generates
	 * interrupt on changing age.
	 * This cycle runs not more than number of channels, because
	 * channel_service_interrupt() routine doesn't start the channel again.
	 */
	do {
		struct dim_channel *const *ch = channels;

		state_changed = false;

		while (*ch) {
			state_changed |= channel_service_interrupt(*ch);
			++ch;
		}
	} while (state_changed);
}