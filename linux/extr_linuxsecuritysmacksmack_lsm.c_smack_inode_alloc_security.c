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
struct inode {int /*<<< orphan*/ * i_security; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * new_inode_smack (struct smack_known*) ; 
 struct smack_known* smk_of_current () ; 

__attribute__((used)) static int smack_inode_alloc_security(struct inode *inode)
{
	struct smack_known *skp = smk_of_current();

	inode->i_security = new_inode_smack(skp);
	if (inode->i_security == NULL)
		return -ENOMEM;
	return 0;
}