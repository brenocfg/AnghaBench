#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct obs_display {struct obs_display* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  displays_mutex; struct obs_display* first_display; int /*<<< orphan*/  valid; } ;
struct TYPE_4__ {int /*<<< orphan*/  graphics; } ;
struct TYPE_6__ {TYPE_2__ data; TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_enter_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_leave_context () ; 
 TYPE_3__* obs ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  render_display (struct obs_display*) ; 

__attribute__((used)) static inline void render_displays(void)
{
	struct obs_display *display;

	if (!obs->data.valid)
		return;

	gs_enter_context(obs->video.graphics);

	/* render extra displays/swaps */
	pthread_mutex_lock(&obs->data.displays_mutex);

	display = obs->data.first_display;
	while (display) {
		render_display(display);
		display = display->next;
	}

	pthread_mutex_unlock(&obs->data.displays_mutex);

	gs_leave_context();
}