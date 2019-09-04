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
typedef  int u32 ;
struct gem {int rx_fifo_sz; int rx_pause_off; int rx_pause_on; int rx_buf_sz; scalar_t__ regs; TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ vendor; } ;

/* Variables and functions */
 scalar_t__ GREG_CFG ; 
 int GREG_CFG_ENBUG2FIX ; 
 int GREG_CFG_IBURST ; 
 int GREG_CFG_RONPAULBIT ; 
 int GREG_CFG_RXDMALIM ; 
 int GREG_CFG_TXDMALIM ; 
 scalar_t__ PCI_VENDOR_ID_APPLE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gem_init_pause_thresholds(struct gem *gp)
{
       	u32 cfg;

	/* Calculate pause thresholds.  Setting the OFF threshold to the
	 * full RX fifo size effectively disables PAUSE generation which
	 * is what we do for 10/100 only GEMs which have FIFOs too small
	 * to make real gains from PAUSE.
	 */
	if (gp->rx_fifo_sz <= (2 * 1024)) {
		gp->rx_pause_off = gp->rx_pause_on = gp->rx_fifo_sz;
	} else {
		int max_frame = (gp->rx_buf_sz + 4 + 64) & ~63;
		int off = (gp->rx_fifo_sz - (max_frame * 2));
		int on = off - max_frame;

		gp->rx_pause_off = off;
		gp->rx_pause_on = on;
	}


	/* Configure the chip "burst" DMA mode & enable some
	 * HW bug fixes on Apple version
	 */
       	cfg  = 0;
       	if (gp->pdev->vendor == PCI_VENDOR_ID_APPLE)
		cfg |= GREG_CFG_RONPAULBIT | GREG_CFG_ENBUG2FIX;
#if !defined(CONFIG_SPARC64) && !defined(CONFIG_ALPHA)
       	cfg |= GREG_CFG_IBURST;
#endif
       	cfg |= ((31 << 1) & GREG_CFG_TXDMALIM);
       	cfg |= ((31 << 6) & GREG_CFG_RXDMALIM);
       	writel(cfg, gp->regs + GREG_CFG);

	/* If Infinite Burst didn't stick, then use different
	 * thresholds (and Apple bug fixes don't exist)
	 */
	if (!(readl(gp->regs + GREG_CFG) & GREG_CFG_IBURST)) {
		cfg = ((2 << 1) & GREG_CFG_TXDMALIM);
		cfg |= ((8 << 6) & GREG_CFG_RXDMALIM);
		writel(cfg, gp->regs + GREG_CFG);
	}
}