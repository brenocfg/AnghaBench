#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct delay_data {scalar_t__ msg; int /*<<< orphan*/  packet; } ;
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_4__ {int /*<<< orphan*/  delay_restart_refs; scalar_t__ active_delay_ns; TYPE_3__ delay_data; } ;
typedef  TYPE_1__ obs_output_t ;
typedef  int /*<<< orphan*/  dd ;

/* Variables and functions */
 scalar_t__ DELAY_MSG_PACKET ; 
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_3__*,struct delay_data*,int) ; 
 int /*<<< orphan*/  obs_encoder_packet_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void obs_output_cleanup_delay(obs_output_t *output)
{
	struct delay_data dd;

	while (output->delay_data.size) {
		circlebuf_pop_front(&output->delay_data, &dd, sizeof(dd));
		if (dd.msg == DELAY_MSG_PACKET) {
			obs_encoder_packet_release(&dd.packet);
		}
	}

	output->active_delay_ns = 0;
	os_atomic_set_long(&output->delay_restart_refs, 0);
}