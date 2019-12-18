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
struct file_update_data {int found; int newer; int version; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool newer_than_cache(void *param, obs_data_t *cache_file)
{
	struct file_update_data *input = param;
	const char *name = obs_data_get_string(cache_file, "name");
	int version = (int)obs_data_get_int(cache_file, "version");

	if (strcmp(input->name, name) == 0) {
		input->found = true;
		input->newer = input->version > version;
		return false;
	}

	return true;
}