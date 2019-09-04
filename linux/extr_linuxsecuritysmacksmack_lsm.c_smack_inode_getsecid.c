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
typedef  int /*<<< orphan*/  u32 ;
struct smack_known {int /*<<< orphan*/  smk_secid; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct smack_known* smk_of_inode (struct inode*) ; 

__attribute__((used)) static void smack_inode_getsecid(struct inode *inode, u32 *secid)
{
	struct smack_known *skp = smk_of_inode(inode);

	*secid = skp->smk_secid;
}