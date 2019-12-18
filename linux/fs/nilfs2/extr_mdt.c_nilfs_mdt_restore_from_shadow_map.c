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
struct nilfs_mdt_info {int /*<<< orphan*/  mi_sem; scalar_t__ mi_palloc_cache; struct nilfs_shadow_map* mi_shadow; } ;
struct nilfs_inode_info {int /*<<< orphan*/  i_bmap; int /*<<< orphan*/  i_btnode_cache; } ;
struct inode {int /*<<< orphan*/ * i_mapping; } ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 struct nilfs_mdt_info* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_bmap_restore (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_clear_dirty_pages (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nilfs_copy_back_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_palloc_clear_cache (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void nilfs_mdt_restore_from_shadow_map(struct inode *inode)
{
	struct nilfs_mdt_info *mi = NILFS_MDT(inode);
	struct nilfs_inode_info *ii = NILFS_I(inode);
	struct nilfs_shadow_map *shadow = mi->mi_shadow;

	down_write(&mi->mi_sem);

	if (mi->mi_palloc_cache)
		nilfs_palloc_clear_cache(inode);

	nilfs_clear_dirty_pages(inode->i_mapping, true);
	nilfs_copy_back_pages(inode->i_mapping, &shadow->frozen_data);

	nilfs_clear_dirty_pages(&ii->i_btnode_cache, true);
	nilfs_copy_back_pages(&ii->i_btnode_cache, &shadow->frozen_btnodes);

	nilfs_bmap_restore(ii->i_bmap, &shadow->bmap_store);

	up_write(&mi->mi_sem);
}