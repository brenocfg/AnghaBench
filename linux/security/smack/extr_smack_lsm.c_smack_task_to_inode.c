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
struct task_struct {int dummy; } ;
struct smack_known {int dummy; } ;
struct inode_smack {int /*<<< orphan*/  smk_flags; struct smack_known* smk_inode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMK_INODE_INSTANT ; 
 struct inode_smack* smack_inode (struct inode*) ; 
 struct smack_known* smk_of_task_struct (struct task_struct*) ; 

__attribute__((used)) static void smack_task_to_inode(struct task_struct *p, struct inode *inode)
{
	struct inode_smack *isp = smack_inode(inode);
	struct smack_known *skp = smk_of_task_struct(p);

	isp->smk_inode = skp;
	isp->smk_flags |= SMK_INODE_INSTANT;
}