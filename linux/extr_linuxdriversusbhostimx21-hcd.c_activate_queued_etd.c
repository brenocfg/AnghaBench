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
typedef  int u8 ;
typedef  int u32 ;
struct urb_priv {int active; } ;
struct imx21 {int /*<<< orphan*/  dev; struct etd_priv* etd; } ;
struct etd_priv {int dmem_offset; TYPE_1__* urb; } ;
struct TYPE_2__ {struct urb_priv* hcpriv; } ;

/* Variables and functions */
 int DW1_YBUFSRTAD ; 
 int DW2_DIRPID ; 
 int /*<<< orphan*/  activate_etd (struct imx21*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int etd_readl (struct imx21*,int,int) ; 
 int /*<<< orphan*/  etd_writel (struct imx21*,int,int,int) ; 

__attribute__((used)) static void activate_queued_etd(struct imx21 *imx21,
	struct etd_priv *etd, u32 dmem_offset)
{
	struct urb_priv *urb_priv = etd->urb->hcpriv;
	int etd_num = etd - &imx21->etd[0];
	u32 maxpacket = etd_readl(imx21, etd_num, 1) >> DW1_YBUFSRTAD;
	u8 dir = (etd_readl(imx21, etd_num, 2) >> DW2_DIRPID) & 0x03;

	dev_dbg(imx21->dev, "activating queued ETD %d now DMEM available\n",
		etd_num);
	etd_writel(imx21, etd_num, 1,
	    ((dmem_offset + maxpacket) << DW1_YBUFSRTAD) | dmem_offset);

	etd->dmem_offset = dmem_offset;
	urb_priv->active = 1;
	activate_etd(imx21, etd_num, dir);
}