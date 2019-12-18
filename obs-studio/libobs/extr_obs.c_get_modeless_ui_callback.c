#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct obs_modeless_ui {int /*<<< orphan*/  target; int /*<<< orphan*/  task; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {size_t num; struct obs_modeless_ui* array; } ;
struct TYPE_4__ {TYPE_1__ modeless_ui_callbacks; } ;

/* Variables and functions */
 TYPE_2__* obs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline struct obs_modeless_ui *
get_modeless_ui_callback(const char *id, const char *task, const char *target)
{
	for (size_t i = 0; i < obs->modeless_ui_callbacks.num; i++) {
		struct obs_modeless_ui *callback;
		callback = obs->modeless_ui_callbacks.array + i;

		if (strcmp(callback->id, id) == 0 &&
		    strcmp(callback->task, task) == 0 &&
		    strcmp(callback->target, target) == 0)
			return callback;
	}

	return NULL;
}