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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct rtl8187_priv {TYPE_2__* map; int /*<<< orphan*/  io_mutex; TYPE_1__* io_dmabuf; int /*<<< orphan*/  udev; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int /*<<< orphan*/  RFPinsSelect; int /*<<< orphan*/  RFPinsOutput; int /*<<< orphan*/  RFPinsEnable; } ;
struct TYPE_3__ {int /*<<< orphan*/  bits16; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  RTL8187_REQT_WRITE ; 
 int /*<<< orphan*/  RTL8187_REQ_SET_REG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtl818x_ioread16 (struct rtl8187_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8225_write_8051(struct ieee80211_hw *dev, u8 addr, __le16 data)
{
	struct rtl8187_priv *priv = dev->priv;
	u16 reg80, reg82, reg84;

	reg80 = rtl818x_ioread16(priv, &priv->map->RFPinsOutput);
	reg82 = rtl818x_ioread16(priv, &priv->map->RFPinsEnable);
	reg84 = rtl818x_ioread16(priv, &priv->map->RFPinsSelect);

	reg80 &= ~(0x3 << 2);
	reg84 &= ~0xF;

	rtl818x_iowrite16(priv, &priv->map->RFPinsEnable, reg82 | 0x0007);
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, reg84 | 0x0007);
	udelay(10);

	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, reg80 | (1 << 2));
	udelay(2);

	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, reg80);
	udelay(10);

	mutex_lock(&priv->io_mutex);

	priv->io_dmabuf->bits16 = data;
	usb_control_msg(priv->udev, usb_sndctrlpipe(priv->udev, 0),
			RTL8187_REQ_SET_REG, RTL8187_REQT_WRITE,
			addr, 0x8225, &priv->io_dmabuf->bits16, sizeof(data),
			HZ / 2);

	mutex_unlock(&priv->io_mutex);

	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, reg80 | (1 << 2));
	udelay(10);

	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, reg80 | (1 << 2));
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, reg84);
}