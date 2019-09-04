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
struct TYPE_2__ {int level; } ;
struct dim_channel {int /*<<< orphan*/  done_sw_buffers_number; TYPE_1__ state; } ;
struct dim_ch_state_t {int ready; int /*<<< orphan*/  done_buffers; } ;

/* Variables and functions */

struct dim_ch_state_t *dim_get_channel_state(struct dim_channel *ch,
					     struct dim_ch_state_t *state_ptr)
{
	if (!ch || !state_ptr)
		return NULL;

	state_ptr->ready = ch->state.level < 2;
	state_ptr->done_buffers = ch->done_sw_buffers_number;

	return state_ptr;
}