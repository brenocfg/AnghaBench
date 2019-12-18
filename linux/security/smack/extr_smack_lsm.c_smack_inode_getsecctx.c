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
struct smack_known {void* smk_known; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct smack_known* smk_of_inode (struct inode*) ; 
 int /*<<< orphan*/  strlen (void*) ; 

__attribute__((used)) static int smack_inode_getsecctx(struct inode *inode, void **ctx, u32 *ctxlen)
{
	struct smack_known *skp = smk_of_inode(inode);

	*ctx = skp->smk_known;
	*ctxlen = strlen(skp->smk_known);
	return 0;
}