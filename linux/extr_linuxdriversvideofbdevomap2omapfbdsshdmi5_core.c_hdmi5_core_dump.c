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
struct seq_file {int dummy; } ;
struct hdmi_core_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CORE_FC_AVICONF0 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_AVICONF1 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_AVICONF2 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_AVIVID ; 
 int /*<<< orphan*/  HDMI_CORE_FC_CH0PREAM ; 
 int /*<<< orphan*/  HDMI_CORE_FC_CH1PREAM ; 
 int /*<<< orphan*/  HDMI_CORE_FC_CH2PREAM ; 
 int /*<<< orphan*/  HDMI_CORE_FC_CTRLDUR ; 
 int /*<<< orphan*/  HDMI_CORE_FC_EXCTRLDUR ; 
 int /*<<< orphan*/  HDMI_CORE_FC_EXCTRLSPAC ; 
 int /*<<< orphan*/  HDMI_CORE_FC_HSYNCINDELAY0 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_HSYNCINDELAY1 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_HSYNCINWIDTH0 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_HSYNCINWIDTH1 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_INHACTIV0 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_INHACTIV1 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_INHBLANK0 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_INHBLANK1 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_INVACTIV0 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_INVACTIV1 ; 
 int /*<<< orphan*/  HDMI_CORE_FC_INVBLANK ; 
 int /*<<< orphan*/  HDMI_CORE_FC_INVIDCONF ; 
 int /*<<< orphan*/  HDMI_CORE_FC_PRCONF ; 
 int /*<<< orphan*/  HDMI_CORE_FC_VSYNCINDELAY ; 
 int /*<<< orphan*/  HDMI_CORE_FC_VSYNCINWIDTH ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_ADDRESS ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_CTLINT ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_DATAI ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_DATAO ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_DIV ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_FS_SCL_HCNT_0_ADDR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_FS_SCL_HCNT_1_ADDR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_FS_SCL_LCNT_0_ADDR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_FS_SCL_LCNT_1_ADDR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_INT ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_OPERATION ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_SDA_HOLD_ADDR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_SEGADDR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_SEGPTR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_SLAVE ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_SOFTRSTZ ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_SS_SCL_HCNT_0_ADDR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_SS_SCL_HCNT_1_ADDR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_SS_SCL_LCNT_0_ADDR ; 
 int /*<<< orphan*/  HDMI_CORE_I2CM_SS_SCL_LCNT_1_ADDR ; 
 int /*<<< orphan*/  HDMI_CORE_MC_CLKDIS ; 
 int /*<<< orphan*/  HDMI_CORE_MC_FLOWCTRL ; 
 int /*<<< orphan*/  HDMI_CORE_MC_LOCKONCLOCK ; 
 int /*<<< orphan*/  HDMI_CORE_MC_PHYRSTZ ; 
 int /*<<< orphan*/  HDMI_CORE_MC_SWRSTZREQ ; 
 int /*<<< orphan*/  hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 

void hdmi5_core_dump(struct hdmi_core_data *core, struct seq_file *s)
{

#define DUMPCORE(r) seq_printf(s, "%-35s %08x\n", #r,\
		hdmi_read_reg(core->base, r))

	DUMPCORE(HDMI_CORE_FC_INVIDCONF);
	DUMPCORE(HDMI_CORE_FC_INHACTIV0);
	DUMPCORE(HDMI_CORE_FC_INHACTIV1);
	DUMPCORE(HDMI_CORE_FC_INHBLANK0);
	DUMPCORE(HDMI_CORE_FC_INHBLANK1);
	DUMPCORE(HDMI_CORE_FC_INVACTIV0);
	DUMPCORE(HDMI_CORE_FC_INVACTIV1);
	DUMPCORE(HDMI_CORE_FC_INVBLANK);
	DUMPCORE(HDMI_CORE_FC_HSYNCINDELAY0);
	DUMPCORE(HDMI_CORE_FC_HSYNCINDELAY1);
	DUMPCORE(HDMI_CORE_FC_HSYNCINWIDTH0);
	DUMPCORE(HDMI_CORE_FC_HSYNCINWIDTH1);
	DUMPCORE(HDMI_CORE_FC_VSYNCINDELAY);
	DUMPCORE(HDMI_CORE_FC_VSYNCINWIDTH);
	DUMPCORE(HDMI_CORE_FC_CTRLDUR);
	DUMPCORE(HDMI_CORE_FC_EXCTRLDUR);
	DUMPCORE(HDMI_CORE_FC_EXCTRLSPAC);
	DUMPCORE(HDMI_CORE_FC_CH0PREAM);
	DUMPCORE(HDMI_CORE_FC_CH1PREAM);
	DUMPCORE(HDMI_CORE_FC_CH2PREAM);
	DUMPCORE(HDMI_CORE_FC_AVICONF0);
	DUMPCORE(HDMI_CORE_FC_AVICONF1);
	DUMPCORE(HDMI_CORE_FC_AVICONF2);
	DUMPCORE(HDMI_CORE_FC_AVIVID);
	DUMPCORE(HDMI_CORE_FC_PRCONF);

	DUMPCORE(HDMI_CORE_MC_CLKDIS);
	DUMPCORE(HDMI_CORE_MC_SWRSTZREQ);
	DUMPCORE(HDMI_CORE_MC_FLOWCTRL);
	DUMPCORE(HDMI_CORE_MC_PHYRSTZ);
	DUMPCORE(HDMI_CORE_MC_LOCKONCLOCK);

	DUMPCORE(HDMI_CORE_I2CM_SLAVE);
	DUMPCORE(HDMI_CORE_I2CM_ADDRESS);
	DUMPCORE(HDMI_CORE_I2CM_DATAO);
	DUMPCORE(HDMI_CORE_I2CM_DATAI);
	DUMPCORE(HDMI_CORE_I2CM_OPERATION);
	DUMPCORE(HDMI_CORE_I2CM_INT);
	DUMPCORE(HDMI_CORE_I2CM_CTLINT);
	DUMPCORE(HDMI_CORE_I2CM_DIV);
	DUMPCORE(HDMI_CORE_I2CM_SEGADDR);
	DUMPCORE(HDMI_CORE_I2CM_SOFTRSTZ);
	DUMPCORE(HDMI_CORE_I2CM_SEGPTR);
	DUMPCORE(HDMI_CORE_I2CM_SS_SCL_HCNT_1_ADDR);
	DUMPCORE(HDMI_CORE_I2CM_SS_SCL_HCNT_0_ADDR);
	DUMPCORE(HDMI_CORE_I2CM_SS_SCL_LCNT_1_ADDR);
	DUMPCORE(HDMI_CORE_I2CM_SS_SCL_LCNT_0_ADDR);
	DUMPCORE(HDMI_CORE_I2CM_FS_SCL_HCNT_1_ADDR);
	DUMPCORE(HDMI_CORE_I2CM_FS_SCL_HCNT_0_ADDR);
	DUMPCORE(HDMI_CORE_I2CM_FS_SCL_LCNT_1_ADDR);
	DUMPCORE(HDMI_CORE_I2CM_FS_SCL_LCNT_0_ADDR);
	DUMPCORE(HDMI_CORE_I2CM_SDA_HOLD_ADDR);
}