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
struct nilfs_shadow_map {int /*<<< orphan*/  frozen_btnodes; int /*<<< orphan*/  frozen_data; } ;
struct nilfs_mdt_info {int /*<<< orphan*/  mi_sem; struct nilfs_shadow_map* mi_shadow; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nilfs_mdt_info* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_release_frozen_buffers (struct nilfs_shadow_map*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void nilfs_mdt_clear_shadow_map(struct inode *inode)
{
	struct nilfs_mdt_info *mi = NILFS_MDT(inode);
	struct nilfs_shadow_map *shadow = mi->mi_shadow;

	down_write(&mi->mi_sem);
	nilfs_release_frozen_buffers(shadow);
	truncate_inode_pages(&shadow->frozen_data, 0);
	truncate_inode_pages(&shadow->frozen_btnodes, 0);
	up_write(&mi->mi_sem);
}