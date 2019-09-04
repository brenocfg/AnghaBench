#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hdmi_wp_data {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ phy; } ;

/* Variables and functions */
 int FLD_MOD (int,int,int,int) ; 
 int HDMI_IRQ_LINK_CONNECT ; 
 int HDMI_IRQ_LINK_DISCONNECT ; 
 int /*<<< orphan*/  HDMI_PHYPWRCMD_LDOON ; 
 int /*<<< orphan*/  HDMI_PHYPWRCMD_OFF ; 
 int /*<<< orphan*/  HDMI_PHYPWRCMD_TXON ; 
 int /*<<< orphan*/  HDMI_TXPHY_PAD_CFG_CTRL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__ hdmi ; 
 int hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdmi_wp_get_irqstatus (struct hdmi_wp_data*) ; 
 int /*<<< orphan*/  hdmi_wp_set_irqstatus (struct hdmi_wp_data*,int) ; 
 int /*<<< orphan*/  hdmi_wp_set_phy_pwr (struct hdmi_wp_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t hdmi_irq_handler(int irq, void *data)
{
	struct hdmi_wp_data *wp = data;
	u32 irqstatus;

	irqstatus = hdmi_wp_get_irqstatus(wp);
	hdmi_wp_set_irqstatus(wp, irqstatus);

	if ((irqstatus & HDMI_IRQ_LINK_CONNECT) &&
			irqstatus & HDMI_IRQ_LINK_DISCONNECT) {
		u32 v;
		/*
		 * If we get both connect and disconnect interrupts at the same
		 * time, turn off the PHY, clear interrupts, and restart, which
		 * raises connect interrupt if a cable is connected, or nothing
		 * if cable is not connected.
		 */

		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_OFF);

		/*
		 * We always get bogus CONNECT & DISCONNECT interrupts when
		 * setting the PHY to LDOON. To ignore those, we force the RXDET
		 * line to 0 until the PHY power state has been changed.
		 */
		v = hdmi_read_reg(hdmi.phy.base, HDMI_TXPHY_PAD_CFG_CTRL);
		v = FLD_MOD(v, 1, 15, 15); /* FORCE_RXDET_HIGH */
		v = FLD_MOD(v, 0, 14, 7); /* RXDET_LINE */
		hdmi_write_reg(hdmi.phy.base, HDMI_TXPHY_PAD_CFG_CTRL, v);

		hdmi_wp_set_irqstatus(wp, HDMI_IRQ_LINK_CONNECT |
				HDMI_IRQ_LINK_DISCONNECT);

		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);

		REG_FLD_MOD(hdmi.phy.base, HDMI_TXPHY_PAD_CFG_CTRL, 0, 15, 15);

	} else if (irqstatus & HDMI_IRQ_LINK_CONNECT) {
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_TXON);
	} else if (irqstatus & HDMI_IRQ_LINK_DISCONNECT) {
		hdmi_wp_set_phy_pwr(wp, HDMI_PHYPWRCMD_LDOON);
	}

	return IRQ_HANDLED;
}