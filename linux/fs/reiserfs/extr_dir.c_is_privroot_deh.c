#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_de_head {scalar_t__ deh_objectid; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {scalar_t__ k_objectid; } ;
struct TYPE_3__ {struct dentry* priv_root; } ;

/* Variables and functions */
 TYPE_2__* INODE_PKEY (int /*<<< orphan*/ ) ; 
 TYPE_1__* REISERFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 

__attribute__((used)) static inline bool is_privroot_deh(struct inode *dir, struct reiserfs_de_head *deh)
{
	struct dentry *privroot = REISERFS_SB(dir->i_sb)->priv_root;
	return (d_really_is_positive(privroot) &&
	        deh->deh_objectid == INODE_PKEY(d_inode(privroot))->k_objectid);
}