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
struct isp1362_hcd {int /*<<< orphan*/  irqenb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCATLBLKSZ ; 
 int /*<<< orphan*/  HCATLBUFSZ ; 
 int /*<<< orphan*/  HCATLCURR ; 
 int /*<<< orphan*/  HCATLDTC ; 
 int /*<<< orphan*/  HCATLDTCTO ; 
 int /*<<< orphan*/  HCATLLAST ; 
 int /*<<< orphan*/  HCATLSKIP ; 
 int /*<<< orphan*/  HCBUFSTAT ; 
 int /*<<< orphan*/  HCCHIPID ; 
 int /*<<< orphan*/  HCCMDSTAT ; 
 int /*<<< orphan*/  HCCONTROL ; 
 int /*<<< orphan*/  HCDIRADDR ; 
 int /*<<< orphan*/  HCDMACFG ; 
 int /*<<< orphan*/  HCFMINTVL ; 
 int /*<<< orphan*/  HCFMNUM ; 
 int /*<<< orphan*/  HCFMREM ; 
 int /*<<< orphan*/  HCHWCFG ; 
 int /*<<< orphan*/  HCINTENB ; 
 int /*<<< orphan*/  HCINTLBLKSZ ; 
 int /*<<< orphan*/  HCINTLBUFSZ ; 
 int /*<<< orphan*/  HCINTLCURR ; 
 int /*<<< orphan*/  HCINTLDONE ; 
 int /*<<< orphan*/  HCINTLLAST ; 
 int /*<<< orphan*/  HCINTLSKIP ; 
 int /*<<< orphan*/  HCINTSTAT ; 
 int /*<<< orphan*/  HCISTLBUFSZ ; 
 int /*<<< orphan*/  HCISTLRATE ; 
 int /*<<< orphan*/  HCLSTHRESH ; 
 int /*<<< orphan*/  HCREVISION ; 
 int /*<<< orphan*/  HCRHDESCA ; 
 int /*<<< orphan*/  HCRHDESCB ; 
 int /*<<< orphan*/  HCRHPORT1 ; 
 int /*<<< orphan*/  HCRHPORT2 ; 
 int /*<<< orphan*/  HCRHSTATUS ; 
 int /*<<< orphan*/  HCSCRATCH ; 
 int /*<<< orphan*/  HCXFERCTR ; 
 int /*<<< orphan*/  HCuPINT ; 
 int /*<<< orphan*/  HCuPINTENB ; 
 int /*<<< orphan*/  ISP1362_REG_HCuPINTENB ; 
 int /*<<< orphan*/  ISP1362_REG_NO (int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  isp1362_show_reg (struct isp1362_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __attribute__((__unused__)) isp1362_show_regs(struct isp1362_hcd *isp1362_hcd)
{
	isp1362_show_reg(isp1362_hcd, HCREVISION);
	isp1362_show_reg(isp1362_hcd, HCCONTROL);
	isp1362_show_reg(isp1362_hcd, HCCMDSTAT);
	isp1362_show_reg(isp1362_hcd, HCINTSTAT);
	isp1362_show_reg(isp1362_hcd, HCINTENB);
	isp1362_show_reg(isp1362_hcd, HCFMINTVL);
	isp1362_show_reg(isp1362_hcd, HCFMREM);
	isp1362_show_reg(isp1362_hcd, HCFMNUM);
	isp1362_show_reg(isp1362_hcd, HCLSTHRESH);
	isp1362_show_reg(isp1362_hcd, HCRHDESCA);
	isp1362_show_reg(isp1362_hcd, HCRHDESCB);
	isp1362_show_reg(isp1362_hcd, HCRHSTATUS);
	isp1362_show_reg(isp1362_hcd, HCRHPORT1);
	isp1362_show_reg(isp1362_hcd, HCRHPORT2);

	isp1362_show_reg(isp1362_hcd, HCHWCFG);
	isp1362_show_reg(isp1362_hcd, HCDMACFG);
	isp1362_show_reg(isp1362_hcd, HCXFERCTR);
	isp1362_show_reg(isp1362_hcd, HCuPINT);

	if (in_interrupt())
		DBG(0, "%-12s[%02x]:     %04x\n", "HCuPINTENB",
			 ISP1362_REG_NO(ISP1362_REG_HCuPINTENB), isp1362_hcd->irqenb);
	else
		isp1362_show_reg(isp1362_hcd, HCuPINTENB);
	isp1362_show_reg(isp1362_hcd, HCCHIPID);
	isp1362_show_reg(isp1362_hcd, HCSCRATCH);
	isp1362_show_reg(isp1362_hcd, HCBUFSTAT);
	isp1362_show_reg(isp1362_hcd, HCDIRADDR);
	/* Access would advance fifo
	 * isp1362_show_reg(isp1362_hcd, HCDIRDATA);
	 */
	isp1362_show_reg(isp1362_hcd, HCISTLBUFSZ);
	isp1362_show_reg(isp1362_hcd, HCISTLRATE);
	isp1362_show_reg(isp1362_hcd, HCINTLBUFSZ);
	isp1362_show_reg(isp1362_hcd, HCINTLBLKSZ);
	isp1362_show_reg(isp1362_hcd, HCINTLDONE);
	isp1362_show_reg(isp1362_hcd, HCINTLSKIP);
	isp1362_show_reg(isp1362_hcd, HCINTLLAST);
	isp1362_show_reg(isp1362_hcd, HCINTLCURR);
	isp1362_show_reg(isp1362_hcd, HCATLBUFSZ);
	isp1362_show_reg(isp1362_hcd, HCATLBLKSZ);
	/* only valid after ATL_DONE interrupt
	 * isp1362_show_reg(isp1362_hcd, HCATLDONE);
	 */
	isp1362_show_reg(isp1362_hcd, HCATLSKIP);
	isp1362_show_reg(isp1362_hcd, HCATLLAST);
	isp1362_show_reg(isp1362_hcd, HCATLCURR);
	isp1362_show_reg(isp1362_hcd, HCATLDTC);
	isp1362_show_reg(isp1362_hcd, HCATLDTCTO);
}