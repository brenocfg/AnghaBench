#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  kprojid_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_projid; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  ext4_has_feature_project (int /*<<< orphan*/ ) ; 

int ext4_get_projid(struct inode *inode, kprojid_t *projid)
{
	if (!ext4_has_feature_project(inode->i_sb))
		return -EOPNOTSUPP;
	*projid = EXT4_I(inode)->i_projid;
	return 0;
}