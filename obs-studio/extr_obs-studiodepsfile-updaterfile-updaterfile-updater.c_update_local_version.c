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
struct update_info {int /*<<< orphan*/  local_package; int /*<<< orphan*/  cache_package; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_local_to_cache (struct update_info*,char*) ; 
 int /*<<< orphan*/  enum_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct update_info*) ; 
 int /*<<< orphan*/  obs_data_addref (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_files_to_local ; 

__attribute__((used)) static int update_local_version(struct update_info *info)
{
	int local_version;
	int cache_version = 0;

	local_version = (int)obs_data_get_int(info->local_package, "version");
	cache_version = (int)obs_data_get_int(info->cache_package, "version");

	/* if local cached version is out of date, copy new version */
	if (cache_version < local_version) {
		enum_files(info->local_package, update_files_to_local, info);
		copy_local_to_cache(info, "package.json");

		obs_data_release(info->cache_package);
		obs_data_addref(info->local_package);
		info->cache_package = info->local_package;

		return local_version;
	}

	return cache_version;
}