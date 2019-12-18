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
struct orangefs_inode_s {int /*<<< orphan*/  xattr_sem; int /*<<< orphan*/  vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void orangefs_inode_cache_ctor(void *req)
{
	struct orangefs_inode_s *orangefs_inode = req;

	inode_init_once(&orangefs_inode->vfs_inode);
	init_rwsem(&orangefs_inode->xattr_sem);
}