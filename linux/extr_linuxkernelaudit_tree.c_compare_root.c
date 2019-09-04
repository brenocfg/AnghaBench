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
struct vfsmount {int /*<<< orphan*/  mnt_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_backing_inode (int /*<<< orphan*/ ) ; 
 unsigned long inode_to_key (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compare_root(struct vfsmount *mnt, void *arg)
{
	return inode_to_key(d_backing_inode(mnt->mnt_root)) ==
	       (unsigned long)arg;
}