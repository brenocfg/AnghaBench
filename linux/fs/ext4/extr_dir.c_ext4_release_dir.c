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
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_htree_free_dir_info (scalar_t__) ; 

__attribute__((used)) static int ext4_release_dir(struct inode *inode, struct file *filp)
{
	if (filp->private_data)
		ext4_htree_free_dir_info(filp->private_data);

	return 0;
}