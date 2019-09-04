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
typedef  int u8 ;
typedef  size_t u16 ;
struct spmi_pmic_arb {TYPE_3__* spmic; TYPE_2__* ver_ops; TYPE_1__* apid_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* irq_clear ) (struct spmi_pmic_arb*,size_t) ;} ;
struct TYPE_4__ {size_t ppid; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ QPNPINT_REG_EN_CLR ; 
 scalar_t__ QPNPINT_REG_LATCHED_CLR ; 
 int /*<<< orphan*/  SPMI_CMD_EXT_WRITEL ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*,int,size_t) ; 
 scalar_t__ pmic_arb_write_cmd (TYPE_3__*,int /*<<< orphan*/ ,int,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  stub1 (struct spmi_pmic_arb*,size_t) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_irq(struct spmi_pmic_arb *pmic_arb, u16 apid, int id)
{
	u16 ppid = pmic_arb->apid_data[apid].ppid;
	u8 sid = ppid >> 8;
	u8 per = ppid & 0xFF;
	u8 irq_mask = BIT(id);

	writel_relaxed(irq_mask, pmic_arb->ver_ops->irq_clear(pmic_arb, apid));

	if (pmic_arb_write_cmd(pmic_arb->spmic, SPMI_CMD_EXT_WRITEL, sid,
			(per << 8) + QPNPINT_REG_LATCHED_CLR, &irq_mask, 1))
		dev_err_ratelimited(&pmic_arb->spmic->dev, "failed to ack irq_mask = 0x%x for ppid = %x\n",
				irq_mask, ppid);

	if (pmic_arb_write_cmd(pmic_arb->spmic, SPMI_CMD_EXT_WRITEL, sid,
			       (per << 8) + QPNPINT_REG_EN_CLR, &irq_mask, 1))
		dev_err_ratelimited(&pmic_arb->spmic->dev, "failed to ack irq_mask = 0x%x for ppid = %x\n",
				irq_mask, ppid);
}