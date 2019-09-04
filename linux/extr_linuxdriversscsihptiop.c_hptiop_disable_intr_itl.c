#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {TYPE_2__* iop; } ;
struct TYPE_4__ {TYPE_3__ itl; } ;
struct hptiop_hba {TYPE_1__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  outbound_intmask; } ;

/* Variables and functions */
 int IOPMU_OUTBOUND_INT_MSG0 ; 
 int IOPMU_OUTBOUND_INT_POSTQUEUE ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hptiop_disable_intr_itl(struct hptiop_hba *hba)
{
	u32 int_mask;

	int_mask = readl(&hba->u.itl.iop->outbound_intmask);
	writel(int_mask |
		IOPMU_OUTBOUND_INT_MSG0 | IOPMU_OUTBOUND_INT_POSTQUEUE,
		&hba->u.itl.iop->outbound_intmask);
	readl(&hba->u.itl.iop->outbound_intmask);
}