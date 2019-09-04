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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {TYPE_1__* iop; } ;
struct TYPE_6__ {TYPE_2__ itl; } ;
struct hptiop_hba {TYPE_3__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  outbound_intstatus; int /*<<< orphan*/  inbound_msgaddr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hptiop_post_msg_itl(struct hptiop_hba *hba, u32 msg)
{
	writel(msg, &hba->u.itl.iop->inbound_msgaddr0);
	readl(&hba->u.itl.iop->outbound_intstatus);
}