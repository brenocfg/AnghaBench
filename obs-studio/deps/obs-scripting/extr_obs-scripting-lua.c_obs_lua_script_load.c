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
struct TYPE_2__ {int loaded; } ;
struct obs_lua_script {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  obs_script_t ;

/* Variables and functions */
 int load_lua_script (struct obs_lua_script*) ; 
 int /*<<< orphan*/  obs_lua_script_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool obs_lua_script_load(obs_script_t *s)
{
	struct obs_lua_script *data = (struct obs_lua_script *)s;
	if (!data->base.loaded) {
		data->base.loaded = load_lua_script(data);
		if (data->base.loaded)
			obs_lua_script_update(s, NULL);
	}

	return data->base.loaded;
}