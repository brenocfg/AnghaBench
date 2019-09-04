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
struct aa_label {int secid; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_FIRST_SECID ; 
 int AA_SECID_INVALID ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  aa_secids ; 
 int idr_alloc (int /*<<< orphan*/ *,struct aa_label*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  secid_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int aa_alloc_secid(struct aa_label *label, gfp_t gfp)
{
	unsigned long flags;
	int ret;

	idr_preload(gfp);
	spin_lock_irqsave(&secid_lock, flags);
	ret = idr_alloc(&aa_secids, label, AA_FIRST_SECID, 0, GFP_ATOMIC);
	spin_unlock_irqrestore(&secid_lock, flags);
	idr_preload_end();

	if (ret < 0) {
		label->secid = AA_SECID_INVALID;
		return ret;
	}

	AA_BUG(ret == AA_SECID_INVALID);
	label->secid = ret;
	return 0;
}