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
struct nilfs_shadow_map {int /*<<< orphan*/  frozen_btnodes; int /*<<< orphan*/  frozen_data; int /*<<< orphan*/  frozen_buffers; } ;
struct nilfs_mdt_info {struct nilfs_shadow_map* mi_shadow; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nilfs_mdt_info* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  address_space_init_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_mapping_init (int /*<<< orphan*/ *,struct inode*) ; 

int nilfs_mdt_setup_shadow_map(struct inode *inode,
			       struct nilfs_shadow_map *shadow)
{
	struct nilfs_mdt_info *mi = NILFS_MDT(inode);

	INIT_LIST_HEAD(&shadow->frozen_buffers);
	address_space_init_once(&shadow->frozen_data);
	nilfs_mapping_init(&shadow->frozen_data, inode);
	address_space_init_once(&shadow->frozen_btnodes);
	nilfs_mapping_init(&shadow->frozen_btnodes, inode);
	mi->mi_shadow = shadow;
	return 0;
}