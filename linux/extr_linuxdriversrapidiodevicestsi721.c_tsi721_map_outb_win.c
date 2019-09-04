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
typedef  int u64 ;
typedef  int u32 ;
typedef  void* u16 ;
struct tsi721_obw_bar {int free; } ;
struct tsi721_ob_win {int rstart; int base; void* destid; } ;
struct tsi721_device {scalar_t__ obwin_cnt; scalar_t__ regs; TYPE_1__* pdev; struct tsi721_ob_win* ob_win; struct tsi721_obw_bar* p2r_bar; } ;
struct rio_mport {struct tsi721_device* priv; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OBW ; 
 scalar_t__ TSI721_LUT_DATA0 ; 
 int TSI721_LUT_DATA0_ADD ; 
 int TSI721_LUT_DATA0_NREAD ; 
 int TSI721_LUT_DATA0_NWR ; 
 scalar_t__ TSI721_LUT_DATA1 ; 
 scalar_t__ TSI721_LUT_DATA2 ; 
 scalar_t__ TSI721_OBWINLB (int) ; 
 int TSI721_OBWINLB_BA ; 
 int TSI721_OBWINLB_WEN ; 
 scalar_t__ TSI721_OBWINSZ (int) ; 
 scalar_t__ TSI721_OBWINUB (int) ; 
 int TSI721_OBWIN_SIZE (int) ; 
 int TSI721_PC2SR_ZONES ; 
 scalar_t__ TSI721_ZONE_SEL ; 
 int TSI721_ZONE_SEL_GO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int tsi721_obw_alloc (struct tsi721_device*,struct tsi721_obw_bar*,int,int*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tsi721_map_outb_win(struct rio_mport *mport, u16 destid, u64 rstart,
			u32 size, u32 flags, dma_addr_t *laddr)
{
	struct tsi721_device *priv = mport->priv;
	int i;
	struct tsi721_obw_bar *pbar;
	struct tsi721_ob_win *ob_win;
	int obw = -1;
	u32 rval;
	u64 rio_addr;
	u32 zsize;
	int ret = -ENOMEM;

	tsi_debug(OBW, &priv->pdev->dev,
		  "did=%d ra=0x%llx sz=0x%x", destid, rstart, size);

	if (!is_power_of_2(size) || (size < 0x8000) || (rstart & (size - 1)))
		return -EINVAL;

	if (priv->obwin_cnt == 0)
		return -EBUSY;

	for (i = 0; i < 2; i++) {
		if (priv->p2r_bar[i].free >= size) {
			pbar = &priv->p2r_bar[i];
			ret = tsi721_obw_alloc(priv, pbar, size, &obw);
			if (!ret)
				break;
		}
	}

	if (ret)
		return ret;

	WARN_ON(obw == -1);
	ob_win = &priv->ob_win[obw];
	ob_win->destid = destid;
	ob_win->rstart = rstart;
	tsi_debug(OBW, &priv->pdev->dev,
		  "allocated OBW%d @%llx", obw, ob_win->base);

	/*
	 * Configure Outbound Window
	 */

	zsize = size/TSI721_PC2SR_ZONES;
	rio_addr = rstart;

	/*
	 * Program Address Translation Zones:
	 *  This implementation uses all 8 zones associated wit window.
	 */
	for (i = 0; i < TSI721_PC2SR_ZONES; i++) {

		while (ioread32(priv->regs + TSI721_ZONE_SEL) &
			TSI721_ZONE_SEL_GO) {
			udelay(1);
		}

		rval = (u32)(rio_addr & TSI721_LUT_DATA0_ADD) |
			TSI721_LUT_DATA0_NREAD | TSI721_LUT_DATA0_NWR;
		iowrite32(rval, priv->regs + TSI721_LUT_DATA0);
		rval = (u32)(rio_addr >> 32);
		iowrite32(rval, priv->regs + TSI721_LUT_DATA1);
		rval = destid;
		iowrite32(rval, priv->regs + TSI721_LUT_DATA2);

		rval = TSI721_ZONE_SEL_GO | (obw << 3) | i;
		iowrite32(rval, priv->regs + TSI721_ZONE_SEL);

		rio_addr += zsize;
	}

	iowrite32(TSI721_OBWIN_SIZE(size) << 8,
		  priv->regs + TSI721_OBWINSZ(obw));
	iowrite32((u32)(ob_win->base >> 32), priv->regs + TSI721_OBWINUB(obw));
	iowrite32((u32)(ob_win->base & TSI721_OBWINLB_BA) | TSI721_OBWINLB_WEN,
		  priv->regs + TSI721_OBWINLB(obw));

	*laddr = ob_win->base;
	return 0;
}