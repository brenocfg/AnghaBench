#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int stop_code; int /*<<< orphan*/  delay_active; int /*<<< orphan*/  delay_restart_refs; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 scalar_t__ can_reconnect (TYPE_1__*,int) ; 
 scalar_t__ delay_active (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_output_end_data_capture (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_output_end_data_capture_internal (TYPE_1__*,int) ; 
 int /*<<< orphan*/  obs_output_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  output_reconnect (TYPE_1__*) ; 

void obs_output_signal_stop(obs_output_t *output, int code)
{
	if (!obs_output_valid(output, "obs_output_signal_stop"))
		return;

	output->stop_code = code;

	if (can_reconnect(output, code)) {
		if (delay_active(output))
			os_atomic_inc_long(&output->delay_restart_refs);
		obs_output_end_data_capture_internal(output, false);
		output_reconnect(output);
	} else {
		if (delay_active(output))
			os_atomic_set_bool(&output->delay_active, false);
		obs_output_end_data_capture(output);
	}
}