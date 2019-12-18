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
struct jffs2_inode_info {int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jffs2_i_init_once(void *foo)
{
	struct jffs2_inode_info *f = foo;

	mutex_init(&f->sem);
	inode_init_once(&f->vfs_inode);
}