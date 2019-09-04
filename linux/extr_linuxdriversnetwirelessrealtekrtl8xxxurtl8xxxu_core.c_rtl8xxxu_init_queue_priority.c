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
typedef  int u16 ;
struct rtl8xxxu_priv {int ep_tx_count; int /*<<< orphan*/ * out_ep; int /*<<< orphan*/  udev; void** pipe_out; int /*<<< orphan*/  ep_tx_normal_queue; int /*<<< orphan*/  ep_tx_high_queue; int /*<<< orphan*/  ep_tx_low_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_TRXDMA_CTRL ; 
 int TRXDMA_CTRL_BEQ_SHIFT ; 
 int TRXDMA_CTRL_BKQ_SHIFT ; 
 int TRXDMA_CTRL_HIQ_SHIFT ; 
 int TRXDMA_CTRL_MGQ_SHIFT ; 
 int TRXDMA_CTRL_VIQ_SHIFT ; 
 int TRXDMA_CTRL_VOQ_SHIFT ; 
 int TRXDMA_QUEUE_HIGH ; 
 int TRXDMA_QUEUE_LOW ; 
 int TRXDMA_QUEUE_NORMAL ; 
 size_t TXDESC_QUEUE_BE ; 
 size_t TXDESC_QUEUE_BEACON ; 
 size_t TXDESC_QUEUE_BK ; 
 size_t TXDESC_QUEUE_CMD ; 
 size_t TXDESC_QUEUE_HIGH ; 
 size_t TXDESC_QUEUE_MGNT ; 
 size_t TXDESC_QUEUE_VI ; 
 size_t TXDESC_QUEUE_VO ; 
 int rtl8xxxu_read16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 void* usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8xxxu_init_queue_priority(struct rtl8xxxu_priv *priv)
{
	u16 val16, hi, lo;
	u16 hiq, mgq, bkq, beq, viq, voq;
	int hip, mgp, bkp, bep, vip, vop;
	int ret = 0;

	switch (priv->ep_tx_count) {
	case 1:
		if (priv->ep_tx_high_queue) {
			hi = TRXDMA_QUEUE_HIGH;
		} else if (priv->ep_tx_low_queue) {
			hi = TRXDMA_QUEUE_LOW;
		} else if (priv->ep_tx_normal_queue) {
			hi = TRXDMA_QUEUE_NORMAL;
		} else {
			hi = 0;
			ret = -EINVAL;
		}

		hiq = hi;
		mgq = hi;
		bkq = hi;
		beq = hi;
		viq = hi;
		voq = hi;

		hip = 0;
		mgp = 0;
		bkp = 0;
		bep = 0;
		vip = 0;
		vop = 0;
		break;
	case 2:
		if (priv->ep_tx_high_queue && priv->ep_tx_low_queue) {
			hi = TRXDMA_QUEUE_HIGH;
			lo = TRXDMA_QUEUE_LOW;
		} else if (priv->ep_tx_normal_queue && priv->ep_tx_low_queue) {
			hi = TRXDMA_QUEUE_NORMAL;
			lo = TRXDMA_QUEUE_LOW;
		} else if (priv->ep_tx_high_queue && priv->ep_tx_normal_queue) {
			hi = TRXDMA_QUEUE_HIGH;
			lo = TRXDMA_QUEUE_NORMAL;
		} else {
			ret = -EINVAL;
			hi = 0;
			lo = 0;
		}

		hiq = hi;
		mgq = hi;
		bkq = lo;
		beq = lo;
		viq = hi;
		voq = hi;

		hip = 0;
		mgp = 0;
		bkp = 1;
		bep = 1;
		vip = 0;
		vop = 0;
		break;
	case 3:
		beq = TRXDMA_QUEUE_LOW;
		bkq = TRXDMA_QUEUE_LOW;
		viq = TRXDMA_QUEUE_NORMAL;
		voq = TRXDMA_QUEUE_HIGH;
		mgq = TRXDMA_QUEUE_HIGH;
		hiq = TRXDMA_QUEUE_HIGH;

		hip = hiq ^ 3;
		mgp = mgq ^ 3;
		bkp = bkq ^ 3;
		bep = beq ^ 3;
		vip = viq ^ 3;
		vop = viq ^ 3;
		break;
	default:
		ret = -EINVAL;
	}

	/*
	 * None of the vendor drivers are configuring the beacon
	 * queue here .... why?
	 */
	if (!ret) {
		val16 = rtl8xxxu_read16(priv, REG_TRXDMA_CTRL);
		val16 &= 0x7;
		val16 |= (voq << TRXDMA_CTRL_VOQ_SHIFT) |
			(viq << TRXDMA_CTRL_VIQ_SHIFT) |
			(beq << TRXDMA_CTRL_BEQ_SHIFT) |
			(bkq << TRXDMA_CTRL_BKQ_SHIFT) |
			(mgq << TRXDMA_CTRL_MGQ_SHIFT) |
			(hiq << TRXDMA_CTRL_HIQ_SHIFT);
		rtl8xxxu_write16(priv, REG_TRXDMA_CTRL, val16);

		priv->pipe_out[TXDESC_QUEUE_VO] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[vop]);
		priv->pipe_out[TXDESC_QUEUE_VI] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[vip]);
		priv->pipe_out[TXDESC_QUEUE_BE] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[bep]);
		priv->pipe_out[TXDESC_QUEUE_BK] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[bkp]);
		priv->pipe_out[TXDESC_QUEUE_BEACON] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[0]);
		priv->pipe_out[TXDESC_QUEUE_MGNT] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[mgp]);
		priv->pipe_out[TXDESC_QUEUE_HIGH] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[hip]);
		priv->pipe_out[TXDESC_QUEUE_CMD] =
			usb_sndbulkpipe(priv->udev, priv->out_ep[0]);
	}

	return ret;
}