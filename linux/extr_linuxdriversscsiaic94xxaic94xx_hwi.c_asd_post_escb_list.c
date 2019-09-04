#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pend_q_lock; scalar_t__ scbpro; } ;
struct asd_ha_struct {TYPE_1__ seq; } ;
struct asd_ascb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCBPRO ; 
 int /*<<< orphan*/  asd_swap_head_scb (struct asd_ha_struct*,struct asd_ascb*) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int asd_post_escb_list(struct asd_ha_struct *asd_ha, struct asd_ascb *ascb,
		       int num)
{
	unsigned long flags;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	asd_swap_head_scb(asd_ha, ascb);
	asd_ha->seq.scbpro += num;
	asd_write_reg_dword(asd_ha, SCBPRO, (u32)asd_ha->seq.scbpro);
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);

	return 0;
}