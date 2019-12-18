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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_inode_smack (struct inode*,struct smack_known*) ; 
 struct smack_known* smk_of_current () ; 

__attribute__((used)) static int smack_inode_alloc_security(struct inode *inode)
{
	struct smack_known *skp = smk_of_current();

	init_inode_smack(inode, skp);
	return 0;
}