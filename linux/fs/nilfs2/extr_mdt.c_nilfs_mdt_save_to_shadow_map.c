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
struct nilfs_shadow_map {int /*<<< orphan*/  bmap_store; int /*<<< orphan*/  frozen_btnodes; int /*<<< orphan*/  frozen_data; } ;
struct nilfs_mdt_info {struct nilfs_shadow_map* mi_shadow; } ;
struct nilfs_inode_info {int /*<<< orphan*/  i_bmap; int /*<<< orphan*/  i_btnode_cache; } ;
struct inode {int /*<<< orphan*/ * i_mapping; } ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 struct nilfs_mdt_info* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  nilfs_bmap_save (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nilfs_copy_dirty_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int nilfs_mdt_save_to_shadow_map(struct inode *inode)
{
	struct nilfs_mdt_info *mi = NILFS_MDT(inode);
	struct nilfs_inode_info *ii = NILFS_I(inode);
	struct nilfs_shadow_map *shadow = mi->mi_shadow;
	int ret;

	ret = nilfs_copy_dirty_pages(&shadow->frozen_data, inode->i_mapping);
	if (ret)
		goto out;

	ret = nilfs_copy_dirty_pages(&shadow->frozen_btnodes,
				     &ii->i_btnode_cache);
	if (ret)
		goto out;

	nilfs_bmap_save(ii->i_bmap, &shadow->bmap_store);
 out:
	return ret;
}