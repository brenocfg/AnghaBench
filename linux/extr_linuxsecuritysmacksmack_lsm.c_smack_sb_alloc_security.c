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
struct superblock_smack {int /*<<< orphan*/ * smk_hat; int /*<<< orphan*/ * smk_floor; int /*<<< orphan*/ * smk_default; int /*<<< orphan*/ * smk_root; } ;
struct super_block {struct superblock_smack* s_security; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct superblock_smack* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_known_floor ; 
 int /*<<< orphan*/  smack_known_hat ; 

__attribute__((used)) static int smack_sb_alloc_security(struct super_block *sb)
{
	struct superblock_smack *sbsp;

	sbsp = kzalloc(sizeof(struct superblock_smack), GFP_KERNEL);

	if (sbsp == NULL)
		return -ENOMEM;

	sbsp->smk_root = &smack_known_floor;
	sbsp->smk_default = &smack_known_floor;
	sbsp->smk_floor = &smack_known_floor;
	sbsp->smk_hat = &smack_known_hat;
	/*
	 * SMK_SB_INITIALIZED will be zero from kzalloc.
	 */
	sb->s_security = sbsp;

	return 0;
}