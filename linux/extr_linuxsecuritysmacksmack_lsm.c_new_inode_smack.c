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

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct inode_smack* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smack_inode_cache ; 

__attribute__((used)) static struct inode_smack *new_inode_smack(struct smack_known *skp)
{
	struct inode_smack *isp;

	isp = kmem_cache_zalloc(smack_inode_cache, GFP_NOFS);
	if (isp == NULL)
		return NULL;

	isp->smk_inode = skp;
	isp->smk_flags = 0;
	mutex_init(&isp->smk_lock);

	return isp;
}