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
struct nilfs_mdt_info {struct nilfs_mdt_info* mi_bgl; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nilfs_mdt_info* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct nilfs_mdt_info*) ; 

void nilfs_mdt_destroy(struct inode *inode)
{
	struct nilfs_mdt_info *mdi = NILFS_MDT(inode);

	kfree(mdi->mi_bgl); /* kfree(NULL) is safe */
	kfree(mdi);
}