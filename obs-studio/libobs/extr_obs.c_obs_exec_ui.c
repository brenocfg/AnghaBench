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
struct obs_modal_ui {int (* exec ) (void*,void*) ;} ;

/* Variables and functions */
 int OBS_UI_CANCEL ; 
 int OBS_UI_NOTFOUND ; 
 int OBS_UI_SUCCESS ; 
 struct obs_modal_ui* get_modal_ui_callback (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  obs ; 
 int stub1 (void*,void*) ; 

int obs_exec_ui(const char *name, const char *task, const char *target,
		void *data, void *ui_data)
{
	struct obs_modal_ui *callback;
	int errorcode = OBS_UI_NOTFOUND;

	if (!obs)
		return errorcode;

	callback = get_modal_ui_callback(name, task, target);
	if (callback) {
		bool success = callback->exec(data, ui_data);
		errorcode = success ? OBS_UI_SUCCESS : OBS_UI_CANCEL;
	}

	return errorcode;
}