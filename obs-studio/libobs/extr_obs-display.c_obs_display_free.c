#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * swap; int /*<<< orphan*/  draw_callbacks; int /*<<< orphan*/  draw_info_mutex; int /*<<< orphan*/  draw_callbacks_mutex; } ;
typedef  TYPE_1__ obs_display_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_swapchain_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void obs_display_free(obs_display_t *display)
{
	pthread_mutex_destroy(&display->draw_callbacks_mutex);
	pthread_mutex_destroy(&display->draw_info_mutex);
	da_free(display->draw_callbacks);

	if (display->swap) {
		gs_swapchain_destroy(display->swap);
		display->swap = NULL;
	}
}