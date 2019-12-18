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
struct smack_known {int dummy; } ;
struct inode_smack {int /*<<< orphan*/  smk_lock; scalar_t__ smk_flags; struct smack_known* smk_inode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct inode_smack* smack_inode (struct inode*) ; 

__attribute__((used)) static void init_inode_smack(struct inode *inode, struct smack_known *skp)
{
	struct inode_smack *isp = smack_inode(inode);

	isp->smk_inode = skp;
	isp->smk_flags = 0;
	mutex_init(&isp->smk_lock);
}