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
struct dfs_cache_vol_info {int /*<<< orphan*/  vi_vol; struct dfs_cache_vol_info* vi_mntdata; struct dfs_cache_vol_info* vi_fullpath; int /*<<< orphan*/  vi_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cifs_cleanup_volume_info_contents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dfs_cache_vol_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void free_vol(struct dfs_cache_vol_info *vi)
{
	list_del(&vi->vi_list);
	kfree(vi->vi_fullpath);
	kfree(vi->vi_mntdata);
	cifs_cleanup_volume_info_contents(&vi->vi_vol);
	kfree(vi);
}