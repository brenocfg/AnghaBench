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
struct obs_modeless_ui {void* (* create ) (void*,void*) ;} ;

/* Variables and functions */
 struct obs_modeless_ui* get_modeless_ui_callback (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  obs ; 
 void* stub1 (void*,void*) ; 

void *obs_create_ui(const char *name, const char *task, const char *target,
		    void *data, void *ui_data)
{
	struct obs_modeless_ui *callback;

	if (!obs)
		return NULL;

	callback = get_modeless_ui_callback(name, task, target);
	return callback ? callback->create(data, ui_data) : NULL;
}