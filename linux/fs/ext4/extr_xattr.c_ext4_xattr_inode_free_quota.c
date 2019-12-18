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
 int /*<<< orphan*/  EXT4_STATE_LUSTRE_EA_INODE ; 
 int /*<<< orphan*/  dquot_free_inode (struct inode*) ; 
 int /*<<< orphan*/  dquot_free_space_nodirty (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up_cluster (struct inode*,size_t) ; 

__attribute__((used)) static void ext4_xattr_inode_free_quota(struct inode *parent,
					struct inode *ea_inode,
					size_t len)
{
	if (ea_inode &&
	    ext4_test_inode_state(ea_inode, EXT4_STATE_LUSTRE_EA_INODE))
		return;
	dquot_free_space_nodirty(parent, round_up_cluster(parent, len));
	dquot_free_inode(parent);
}