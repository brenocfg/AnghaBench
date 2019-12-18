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
struct obs_lua_script {int /*<<< orphan*/  dir; int /*<<< orphan*/  log_chunk; TYPE_1__ base; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  obs_script_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct obs_lua_script*) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void obs_lua_script_destroy(obs_script_t *s)
{
	struct obs_lua_script *data = (struct obs_lua_script *)s;

	if (data) {
		pthread_mutex_destroy(&data->mutex);
		dstr_free(&data->base.path);
		dstr_free(&data->base.file);
		dstr_free(&data->base.desc);
		obs_data_release(data->base.settings);
		dstr_free(&data->log_chunk);
		dstr_free(&data->dir);
		bfree(data);
	}
}