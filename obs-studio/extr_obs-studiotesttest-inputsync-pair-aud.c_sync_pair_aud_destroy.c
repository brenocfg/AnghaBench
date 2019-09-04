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
struct sync_pair_aud {int /*<<< orphan*/  event; int /*<<< orphan*/  thread; scalar_t__ initialized_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct sync_pair_aud*) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static void sync_pair_aud_destroy(void *data)
{
	struct sync_pair_aud *spa = data;

	if (spa) {
		if (spa->initialized_thread) {
			void *ret;
			os_event_signal(spa->event);
			pthread_join(spa->thread, &ret);
		}

		os_event_destroy(spa->event);
		bfree(spa);
	}
}