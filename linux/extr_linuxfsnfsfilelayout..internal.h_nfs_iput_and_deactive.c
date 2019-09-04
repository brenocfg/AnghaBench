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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  nfs_sb_deactive (struct super_block*) ; 

__attribute__((used)) static inline void nfs_iput_and_deactive(struct inode *inode)
{
	if (inode != NULL) {
		struct super_block *sb = inode->i_sb;

		iput(inode);
		nfs_sb_deactive(sb);
	}
}