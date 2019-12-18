#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  idotdot; } ;
struct TYPE_5__ {TYPE_1__ header; } ;
struct TYPE_6__ {TYPE_2__ i_dtroot; } ;

/* Variables and functions */
 TYPE_3__* JFS_IP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_iget (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

struct dentry *jfs_get_parent(struct dentry *dentry)
{
	unsigned long parent_ino;

	parent_ino =
		le32_to_cpu(JFS_IP(d_inode(dentry))->i_dtroot.header.idotdot);

	return d_obtain_alias(jfs_iget(dentry->d_sb, parent_ino));
}