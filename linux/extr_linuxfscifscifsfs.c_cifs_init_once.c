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
struct cifsInodeInfo {int /*<<< orphan*/  lock_sem; int /*<<< orphan*/  vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cifs_init_once(void *inode)
{
	struct cifsInodeInfo *cifsi = inode;

	inode_init_once(&cifsi->vfs_inode);
	init_rwsem(&cifsi->lock_sem);
}