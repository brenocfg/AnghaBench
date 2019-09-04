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
struct coreaudio_data {scalar_t__ unit; int /*<<< orphan*/  exit_event; int /*<<< orphan*/  reconnect_thread; scalar_t__ reconnecting; } ;

/* Variables and functions */
 int /*<<< orphan*/  AudioComponentInstanceDispose (scalar_t__) ; 
 int /*<<< orphan*/  coreaudio_uninit (struct coreaudio_data*) ; 
 int /*<<< orphan*/  os_event_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void coreaudio_shutdown(struct coreaudio_data *ca)
{
	if (ca->reconnecting) {
		os_event_signal(ca->exit_event);
		pthread_join(ca->reconnect_thread, NULL);
		os_event_reset(ca->exit_event);
	}

	coreaudio_uninit(ca);

	if (ca->unit)
		AudioComponentInstanceDispose(ca->unit);
}