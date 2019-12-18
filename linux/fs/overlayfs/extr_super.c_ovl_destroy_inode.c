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
struct ovl_inode {int /*<<< orphan*/  lowerdata; int /*<<< orphan*/  lower; int /*<<< orphan*/  __upperdentry; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 struct ovl_inode* OVL_I (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_dir_cache_free (struct inode*) ; 

__attribute__((used)) static void ovl_destroy_inode(struct inode *inode)
{
	struct ovl_inode *oi = OVL_I(inode);

	dput(oi->__upperdentry);
	iput(oi->lower);
	if (S_ISDIR(inode->i_mode))
		ovl_dir_cache_free(inode);
	else
		iput(oi->lowerdata);
}