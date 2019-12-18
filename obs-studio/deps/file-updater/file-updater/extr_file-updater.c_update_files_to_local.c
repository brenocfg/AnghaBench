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
struct update_info {int /*<<< orphan*/  cache_package; } ;
struct file_update_data {int version; int /*<<< orphan*/  name; int /*<<< orphan*/  found; scalar_t__ newer; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  copy_local_to_cache (struct update_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file_update_data*) ; 
 int /*<<< orphan*/  newer_than_cache ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_get_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool update_files_to_local(void *param, obs_data_t *local_file)
{
	struct update_info *info = param;
	struct file_update_data data = {
		.name = obs_data_get_string(local_file, "name"),
		.version = (int)obs_data_get_int(local_file, "version")};

	enum_files(info->cache_package, newer_than_cache, &data);
	if (data.newer || !data.found)
		copy_local_to_cache(info, data.name);

	return true;
}