#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct alsa_data {int /*<<< orphan*/  abort_event; scalar_t__ reopen_thread; int /*<<< orphan*/  reopen; } ;

/* Variables and functions */
 scalar_t__ os_atomic_load_bool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_event_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (scalar_t__,int /*<<< orphan*/ *) ; 

void _alsa_stop_reopen(struct alsa_data *data)
{
	if (os_atomic_load_bool(&data->reopen))
		os_event_signal(data->abort_event);

	if (data->reopen_thread) {
		pthread_join(data->reopen_thread, NULL);
		data->reopen_thread = 0;
	}

	os_event_reset(data->abort_event);
}