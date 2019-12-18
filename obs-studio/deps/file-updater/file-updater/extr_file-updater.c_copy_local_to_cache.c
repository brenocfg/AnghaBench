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
struct update_info {int /*<<< orphan*/  temp; int /*<<< orphan*/  cache; int /*<<< orphan*/  local; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 char* get_path (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  os_copyfile (char*,char*) ; 
 int /*<<< orphan*/  os_rename (char*,char*) ; 
 int /*<<< orphan*/  os_unlink (char*) ; 

__attribute__((used)) static void copy_local_to_cache(struct update_info *info, const char *file)
{
	char *local_file_path = get_path(info->local, file);
	char *cache_file_path = get_path(info->cache, file);
	char *temp_file_path = get_path(info->temp, file);

	os_copyfile(local_file_path, temp_file_path);
	os_unlink(cache_file_path);
	os_rename(temp_file_path, cache_file_path);

	bfree(local_file_path);
	bfree(cache_file_path);
	bfree(temp_file_path);
}