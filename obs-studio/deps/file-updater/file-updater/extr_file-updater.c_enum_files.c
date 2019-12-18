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
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 size_t obs_data_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_array_item (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_get_array (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enum_files(obs_data_t *package,
		       bool (*enum_func)(void *param, obs_data_t *file),
		       void *param)
{
	obs_data_array_t *array = obs_data_get_array(package, "files");
	size_t num;

	if (!array)
		return;

	num = obs_data_array_count(array);

	for (size_t i = 0; i < num; i++) {
		obs_data_t *file = obs_data_array_item(array, i);
		bool continue_enum = enum_func(param, file);
		obs_data_release(file);

		if (!continue_enum)
			break;
	}

	obs_data_array_release(array);
}