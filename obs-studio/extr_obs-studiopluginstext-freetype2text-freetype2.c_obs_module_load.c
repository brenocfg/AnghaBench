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

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  freetype2_source_info ; 
 char* obs_module_config_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_register_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_mkdirs (char*) ; 

bool obs_module_load()
{
	char *config_dir = obs_module_config_path(NULL);
	if (config_dir) {
		os_mkdirs(config_dir);
		bfree(config_dir);
	}

	obs_register_source(&freetype2_source_info);

	return true;
}