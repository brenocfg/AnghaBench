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
struct nilfs_root {int dummy; } ;
struct nilfs_iget_args {unsigned long ino; int /*<<< orphan*/  for_gc; int /*<<< orphan*/  cno; struct nilfs_root* root; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode* ilookup5 (struct super_block*,unsigned long,int /*<<< orphan*/ ,struct nilfs_iget_args*) ; 
 int /*<<< orphan*/  nilfs_iget_test ; 

struct inode *nilfs_ilookup(struct super_block *sb, struct nilfs_root *root,
			    unsigned long ino)
{
	struct nilfs_iget_args args = {
		.ino = ino, .root = root, .cno = 0, .for_gc = 0
	};

	return ilookup5(sb, ino, nilfs_iget_test, &args);
}