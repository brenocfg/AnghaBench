#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  desc; int /*<<< orphan*/  file; int /*<<< orphan*/  path; } ;
struct obs_python_script {int /*<<< orphan*/  name; int /*<<< orphan*/  dir; TYPE_1__ base; int /*<<< orphan*/  module; } ;
typedef  int /*<<< orphan*/  obs_script_t ;

/* Variables and functions */
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (struct obs_python_script*) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_python () ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ ) ; 
 scalar_t__ python_loaded ; 
 int /*<<< orphan*/  unlock_python () ; 

void obs_python_script_destroy(obs_script_t *s)
{
	struct obs_python_script *data = (struct obs_python_script *)s;

	if (data) {
		if (python_loaded) {
			lock_python();
			Py_XDECREF(data->module);
			unlock_python();
		}

		dstr_free(&data->base.path);
		dstr_free(&data->base.file);
		dstr_free(&data->base.desc);
		obs_data_release(data->base.settings);
		dstr_free(&data->dir);
		dstr_free(&data->name);
		bfree(data);
	}
}