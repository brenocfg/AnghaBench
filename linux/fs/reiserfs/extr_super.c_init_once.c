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
struct reiserfs_inode_info {int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  i_prealloc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_once(void *foo)
{
	struct reiserfs_inode_info *ei = (struct reiserfs_inode_info *)foo;

	INIT_LIST_HEAD(&ei->i_prealloc_list);
	inode_init_once(&ei->vfs_inode);
}