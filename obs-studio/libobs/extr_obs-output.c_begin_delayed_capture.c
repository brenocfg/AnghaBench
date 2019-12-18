#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  reconnecting; int /*<<< orphan*/  interleaved_mutex; int /*<<< orphan*/  delay_capturing; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 scalar_t__ delay_capturing (TYPE_1__*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ reconnecting (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_packet_data (TYPE_1__*) ; 
 int /*<<< orphan*/  signal_reconnect_success (TYPE_1__*) ; 
 int /*<<< orphan*/  signal_start (TYPE_1__*) ; 

__attribute__((used)) static bool begin_delayed_capture(obs_output_t *output)
{
	if (delay_capturing(output))
		return false;

	pthread_mutex_lock(&output->interleaved_mutex);
	reset_packet_data(output);
	os_atomic_set_bool(&output->delay_capturing, true);
	pthread_mutex_unlock(&output->interleaved_mutex);

	if (reconnecting(output)) {
		signal_reconnect_success(output);
		os_atomic_set_bool(&output->reconnecting, false);
	} else {
		signal_start(output);
	}

	return true;
}