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
struct integrity_iint_cache {int /*<<< orphan*/  atomic_flags; scalar_t__ measured_pcrs; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int IMA_APPRAISE ; 
 int /*<<< orphan*/  IMA_CHANGE_XATTR ; 
 int /*<<< orphan*/  IMA_DIGSIG ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ima_policy_flag ; 
 struct integrity_iint_cache* integrity_iint_find (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ima_reset_appraise_flags(struct inode *inode, int digsig)
{
	struct integrity_iint_cache *iint;

	if (!(ima_policy_flag & IMA_APPRAISE) || !S_ISREG(inode->i_mode))
		return;

	iint = integrity_iint_find(inode);
	if (!iint)
		return;
	iint->measured_pcrs = 0;
	set_bit(IMA_CHANGE_XATTR, &iint->atomic_flags);
	if (digsig)
		set_bit(IMA_DIGSIG, &iint->atomic_flags);
	else
		clear_bit(IMA_DIGSIG, &iint->atomic_flags);
}