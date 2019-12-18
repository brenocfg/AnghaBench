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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 char* obs_module_config_path (char*) ; 
 char* obs_module_file (char*) ; 
 int /*<<< orphan*/ * open_json_file (char*) ; 

__attribute__((used)) static json_t *open_services_file(void)
{
	char *file;
	json_t *root = NULL;

	file = obs_module_config_path("services.json");
	if (file) {
		root = open_json_file(file);
		bfree(file);
	}

	if (!root) {
		file = obs_module_file("services.json");
		if (file) {
			root = open_json_file(file);
			bfree(file);
		}
	}

	return root;
}