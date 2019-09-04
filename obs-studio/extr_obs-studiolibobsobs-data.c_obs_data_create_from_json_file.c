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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/ * obs_data_create_from_json (char*) ; 
 char* os_quick_read_utf8_file (char const*) ; 

obs_data_t *obs_data_create_from_json_file(const char *json_file)
{
	char *file_data = os_quick_read_utf8_file(json_file);
	obs_data_t *data = NULL;

	if (file_data) {
		data = obs_data_create_from_json(file_data);
		bfree(file_data);
	}

	return data;
}