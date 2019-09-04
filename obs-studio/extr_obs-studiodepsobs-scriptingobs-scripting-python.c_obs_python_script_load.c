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
struct TYPE_4__ {int loaded; } ;
struct TYPE_3__ {int /*<<< orphan*/  array; } ;
struct obs_python_script {TYPE_2__ base; TYPE_1__ dir; int /*<<< orphan*/  module; } ;
typedef  int /*<<< orphan*/  obs_script_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_python_path (int /*<<< orphan*/ ) ; 
 int load_python_script (struct obs_python_script*) ; 
 int /*<<< orphan*/  lock_python () ; 
 int /*<<< orphan*/  obs_python_script_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ python_loaded ; 
 int /*<<< orphan*/  unlock_python () ; 

bool obs_python_script_load(obs_script_t *s)
{
	struct obs_python_script *data = (struct obs_python_script *)s;
	if (python_loaded && !data->base.loaded) {
		lock_python();
		if (!data->module)
			add_to_python_path(data->dir.array);
		data->base.loaded = load_python_script(data);
		unlock_python();

		if (data->base.loaded)
			obs_python_script_update(s, NULL);
	}

	return data->base.loaded;
}