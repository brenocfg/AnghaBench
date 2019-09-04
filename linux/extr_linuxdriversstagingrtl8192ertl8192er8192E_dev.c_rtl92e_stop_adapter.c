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
struct r8192_priv {int bHwRfOffAction; int /*<<< orphan*/  skb_queue; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skb_aggQ; int /*<<< orphan*/ * skb_waitQ; int /*<<< orphan*/  bSupportRemoteWakeUp; int /*<<< orphan*/  (* SetHwRegHandler ) (struct net_device*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMDR ; 
 int /*<<< orphan*/  CPU_GEN ; 
 int CPU_GEN_SYSTEM_RESET ; 
 int /*<<< orphan*/  HW_VAR_MEDIA_STATUS ; 
 int MAX_QUEUE_SIZE ; 
 int /*<<< orphan*/  MacBlkCtrl ; 
 int /*<<< orphan*/  PMR ; 
 int RT_OP_MODE_NO_LINK ; 
 int /*<<< orphan*/  WFCRC0 ; 
 int /*<<< orphan*/  WFCRC1 ; 
 int /*<<< orphan*/  WFCRC2 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtl92e_readl (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_set_rf_off (struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ,int*) ; 

void rtl92e_stop_adapter(struct net_device *dev, bool reset)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	int i;
	u8	OpMode;
	u8	u1bTmp;
	u32	ulRegRead;

	OpMode = RT_OP_MODE_NO_LINK;
	priv->rtllib->SetHwRegHandler(dev, HW_VAR_MEDIA_STATUS, &OpMode);

	if (!priv->rtllib->bSupportRemoteWakeUp) {
		u1bTmp = 0x0;
		rtl92e_writeb(dev, CMDR, u1bTmp);
	}

	mdelay(20);

	if (!reset) {
		mdelay(150);

		priv->bHwRfOffAction = 2;

		if (!priv->rtllib->bSupportRemoteWakeUp) {
			rtl92e_set_rf_off(dev);
			ulRegRead = rtl92e_readl(dev, CPU_GEN);
			ulRegRead |= CPU_GEN_SYSTEM_RESET;
			rtl92e_writel(dev, CPU_GEN, ulRegRead);
		} else {
			rtl92e_writel(dev, WFCRC0, 0xffffffff);
			rtl92e_writel(dev, WFCRC1, 0xffffffff);
			rtl92e_writel(dev, WFCRC2, 0xffffffff);


			rtl92e_writeb(dev, PMR, 0x5);
			rtl92e_writeb(dev, MacBlkCtrl, 0xa);
		}
	}

	for (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_purge(&priv->rtllib->skb_waitQ[i]);
	for (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_purge(&priv->rtllib->skb_aggQ[i]);

	skb_queue_purge(&priv->skb_queue);
}