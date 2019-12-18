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
struct sinewave_data {int /*<<< orphan*/  event; int /*<<< orphan*/  thread; scalar_t__ initialized_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct sinewave_data*) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static void sinewave_destroy(void *data)
{
	struct sinewave_data *swd = data;

	if (swd) {
		if (swd->initialized_thread) {
			void *ret;
			os_event_signal(swd->event);
			pthread_join(swd->thread, &ret);
		}

		os_event_destroy(swd->event);
		bfree(swd);
	}
}