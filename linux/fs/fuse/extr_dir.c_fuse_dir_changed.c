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

/* Variables and functions */
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  inode_maybe_inc_iversion (struct inode*,int) ; 

__attribute__((used)) static void fuse_dir_changed(struct inode *dir)
{
	fuse_invalidate_attr(dir);
	inode_maybe_inc_iversion(dir, false);
}