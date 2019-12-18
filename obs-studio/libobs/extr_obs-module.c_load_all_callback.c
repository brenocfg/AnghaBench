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
struct obs_module_info {int /*<<< orphan*/  bin_path; int /*<<< orphan*/  data_path; } ;
typedef  int /*<<< orphan*/  obs_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int MODULE_SUCCESS ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_init_module (int /*<<< orphan*/ *) ; 
 int obs_open_module (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_all_callback(void *param, const struct obs_module_info *info)
{
	obs_module_t *module;

	int code = obs_open_module(&module, info->bin_path, info->data_path);
	if (code != MODULE_SUCCESS) {
		blog(LOG_DEBUG, "Failed to load module file '%s': %d",
		     info->bin_path, code);
		return;
	}

	obs_init_module(module);

	UNUSED_PARAMETER(param);
}