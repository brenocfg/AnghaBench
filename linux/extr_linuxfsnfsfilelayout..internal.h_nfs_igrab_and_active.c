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
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct inode* igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  nfs_sb_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct inode *nfs_igrab_and_active(struct inode *inode)
{
	inode = igrab(inode);
	if (inode != NULL && !nfs_sb_active(inode->i_sb)) {
		iput(inode);
		inode = NULL;
	}
	return inode;
}