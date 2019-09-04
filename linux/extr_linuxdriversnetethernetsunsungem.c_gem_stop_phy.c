#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u32 ;
struct TYPE_8__ {TYPE_3__* def; } ;
struct gem {scalar_t__ regs; TYPE_4__ phy_mii; TYPE_1__* dev; scalar_t__ has_wol; } ;
struct TYPE_7__ {TYPE_2__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* suspend ) (TYPE_4__*) ;} ;
struct TYPE_5__ {unsigned char* dev_addr; } ;

/* Variables and functions */
 scalar_t__ MAC_RXCFG ; 
 unsigned char MAC_RXCFG_ENAB ; 
 unsigned char MAC_RXCFG_HFE ; 
 unsigned char MAC_RXCFG_SFCS ; 
 scalar_t__ MAC_RXRST ; 
 unsigned char MAC_RXRST_CMD ; 
 scalar_t__ MAC_TXCFG ; 
 scalar_t__ MAC_TXRST ; 
 unsigned char MAC_TXRST_CMD ; 
 scalar_t__ MAC_XIFCFG ; 
 unsigned char MAC_XIFCFG_GMII ; 
 unsigned char MAC_XIFCFG_LBCK ; 
 scalar_t__ MIF_BBCLK ; 
 scalar_t__ MIF_BBDATA ; 
 scalar_t__ MIF_BBOENAB ; 
 scalar_t__ MIF_CFG ; 
 unsigned char MIF_CFG_BBMODE ; 
 unsigned char MIF_CFG_POLL ; 
 scalar_t__ RXDMA_CFG ; 
 scalar_t__ TXDMA_CFG ; 
 scalar_t__ WOL_MATCH0 ; 
 scalar_t__ WOL_MATCH1 ; 
 scalar_t__ WOL_MATCH2 ; 
 scalar_t__ WOL_MCOUNT ; 
 unsigned char WOL_MCOUNT_M ; 
 unsigned char WOL_MCOUNT_N ; 
 scalar_t__ WOL_WAKECSR ; 
 unsigned char WOL_WAKECSR_ENABLE ; 
 unsigned char WOL_WAKECSR_MII ; 
 scalar_t__ found_mii_phy (struct gem*) ; 
 int /*<<< orphan*/  gem_reset (struct gem*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned char readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  writel (unsigned char,scalar_t__) ; 

__attribute__((used)) static void gem_stop_phy(struct gem *gp, int wol)
{
	u32 mifcfg;

	/* Let the chip settle down a bit, it seems that helps
	 * for sleep mode on some models
	 */
	msleep(10);

	/* Make sure we aren't polling PHY status change. We
	 * don't currently use that feature though
	 */
	mifcfg = readl(gp->regs + MIF_CFG);
	mifcfg &= ~MIF_CFG_POLL;
	writel(mifcfg, gp->regs + MIF_CFG);

	if (wol && gp->has_wol) {
		unsigned char *e = &gp->dev->dev_addr[0];
		u32 csr;

		/* Setup wake-on-lan for MAGIC packet */
		writel(MAC_RXCFG_HFE | MAC_RXCFG_SFCS | MAC_RXCFG_ENAB,
		       gp->regs + MAC_RXCFG);
		writel((e[4] << 8) | e[5], gp->regs + WOL_MATCH0);
		writel((e[2] << 8) | e[3], gp->regs + WOL_MATCH1);
		writel((e[0] << 8) | e[1], gp->regs + WOL_MATCH2);

		writel(WOL_MCOUNT_N | WOL_MCOUNT_M, gp->regs + WOL_MCOUNT);
		csr = WOL_WAKECSR_ENABLE;
		if ((readl(gp->regs + MAC_XIFCFG) & MAC_XIFCFG_GMII) == 0)
			csr |= WOL_WAKECSR_MII;
		writel(csr, gp->regs + WOL_WAKECSR);
	} else {
		writel(0, gp->regs + MAC_RXCFG);
		(void)readl(gp->regs + MAC_RXCFG);
		/* Machine sleep will die in strange ways if we
		 * dont wait a bit here, looks like the chip takes
		 * some time to really shut down
		 */
		msleep(10);
	}

	writel(0, gp->regs + MAC_TXCFG);
	writel(0, gp->regs + MAC_XIFCFG);
	writel(0, gp->regs + TXDMA_CFG);
	writel(0, gp->regs + RXDMA_CFG);

	if (!wol) {
		gem_reset(gp);
		writel(MAC_TXRST_CMD, gp->regs + MAC_TXRST);
		writel(MAC_RXRST_CMD, gp->regs + MAC_RXRST);

		if (found_mii_phy(gp) && gp->phy_mii.def->ops->suspend)
			gp->phy_mii.def->ops->suspend(&gp->phy_mii);

		/* According to Apple, we must set the MDIO pins to this begnign
		 * state or we may 1) eat more current, 2) damage some PHYs
		 */
		writel(mifcfg | MIF_CFG_BBMODE, gp->regs + MIF_CFG);
		writel(0, gp->regs + MIF_BBCLK);
		writel(0, gp->regs + MIF_BBDATA);
		writel(0, gp->regs + MIF_BBOENAB);
		writel(MAC_XIFCFG_GMII | MAC_XIFCFG_LBCK, gp->regs + MAC_XIFCFG);
		(void) readl(gp->regs + MAC_XIFCFG);
	}
}