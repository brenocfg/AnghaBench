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
struct rtl8xxxu_priv {TYPE_1__* udev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  REG_RQPN ; 
 int /*<<< orphan*/  REG_RQPN_NPQ ; 
 int /*<<< orphan*/  REG_RXPKT_NUM ; 
 int /*<<< orphan*/  REG_TXPAUSE ; 
 int RXPKT_NUM_RW_RELEASE_EN ; 
 int RXPKT_NUM_RXDMA_IDLE ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 

int rtl8xxxu_flush_fifo(struct rtl8xxxu_priv *priv)
{
	struct device *dev = &priv->udev->dev;
	u32 val32;
	int retry, retval;

	rtl8xxxu_write8(priv, REG_TXPAUSE, 0xff);

	val32 = rtl8xxxu_read32(priv, REG_RXPKT_NUM);
	val32 |= RXPKT_NUM_RW_RELEASE_EN;
	rtl8xxxu_write32(priv, REG_RXPKT_NUM, val32);

	retry = 100;
	retval = -EBUSY;

	do {
		val32 = rtl8xxxu_read32(priv, REG_RXPKT_NUM);
		if (val32 & RXPKT_NUM_RXDMA_IDLE) {
			retval = 0;
			break;
		}
	} while (retry--);

	rtl8xxxu_write16(priv, REG_RQPN_NPQ, 0);
	rtl8xxxu_write32(priv, REG_RQPN, 0x80000000);
	mdelay(2);

	if (!retry)
		dev_warn(dev, "Failed to flush FIFO\n");

	return retval;
}