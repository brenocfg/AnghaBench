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
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_secids ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,struct aa_label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secid_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void aa_secid_update(u32 secid, struct aa_label *label)
{
	unsigned long flags;

	spin_lock_irqsave(&secid_lock, flags);
	idr_replace(&aa_secids, label, secid);
	spin_unlock_irqrestore(&secid_lock, flags);
}