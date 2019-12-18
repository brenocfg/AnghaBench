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
struct update_info {scalar_t__ etag_remote; scalar_t__ etag_local; int /*<<< orphan*/  temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 int /*<<< orphan*/  init_update (struct update_info*) ; 
 int /*<<< orphan*/  os_rmdir (int /*<<< orphan*/ ) ; 
 int update_local_version (struct update_info*) ; 
 int /*<<< orphan*/  update_remote_version (struct update_info*,int) ; 

__attribute__((used)) static void *update_thread(void *data)
{
	struct update_info *info = data;
	int cur_version;

	if (!init_update(info))
		return NULL;

	cur_version = update_local_version(info);
	update_remote_version(info, cur_version);
	os_rmdir(info->temp);

	if (info->etag_local)
		bfree(info->etag_local);
	if (info->etag_remote)
		bfree(info->etag_remote);

	return NULL;
}