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
struct tsi721_device {int obwin_cnt; TYPE_2__* ob_win; TYPE_1__* p2r_bar; scalar_t__ regs; } ;
struct TYPE_4__ {int active; } ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ free; } ;

/* Variables and functions */
 scalar_t__ TSI721_LUT_DATA0 ; 
 scalar_t__ TSI721_LUT_DATA1 ; 
 scalar_t__ TSI721_LUT_DATA2 ; 
 scalar_t__ TSI721_OBWINLB (int) ; 
 int TSI721_OBWIN_NUM ; 
 int TSI721_PC2SR_ZONES ; 
 scalar_t__ TSI721_ZONE_SEL ; 
 int TSI721_ZONE_SEL_GO ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tsi721_init_pc2sr_mapping(struct tsi721_device *priv)
{
	int i, z;
	u32 rval;

	/* Disable all PC2SR translation windows */
	for (i = 0; i < TSI721_OBWIN_NUM; i++)
		iowrite32(0, priv->regs + TSI721_OBWINLB(i));

	/* Initialize zone lookup tables to avoid ECC errors on reads */
	iowrite32(0, priv->regs + TSI721_LUT_DATA0);
	iowrite32(0, priv->regs + TSI721_LUT_DATA1);
	iowrite32(0, priv->regs + TSI721_LUT_DATA2);

	for (i = 0; i < TSI721_OBWIN_NUM; i++) {
		for (z = 0; z < TSI721_PC2SR_ZONES; z++) {
			while (ioread32(priv->regs + TSI721_ZONE_SEL) &
				TSI721_ZONE_SEL_GO) {
				udelay(1);
			}
			rval = TSI721_ZONE_SEL_GO | (i << 3) | z;
			iowrite32(rval, priv->regs + TSI721_ZONE_SEL);
		}
	}

	if (priv->p2r_bar[0].size == 0 && priv->p2r_bar[1].size == 0) {
		priv->obwin_cnt = 0;
		return;
	}

	priv->p2r_bar[0].free = priv->p2r_bar[0].size;
	priv->p2r_bar[1].free = priv->p2r_bar[1].size;

	for (i = 0; i < TSI721_OBWIN_NUM; i++)
		priv->ob_win[i].active = false;

	priv->obwin_cnt = TSI721_OBWIN_NUM;
}