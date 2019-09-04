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
typedef  int /*<<< orphan*/  u8 ;
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct panda_usb_ctx {int dummy; } ;
struct panda_usb_can_msg {int dummy; } ;
struct panda_inf_priv {int /*<<< orphan*/  netdev; TYPE_1__* priv_dev; int /*<<< orphan*/  tx_submitted; } ;
typedef  int netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PANDA_USB_TX_BUFF_SIZE ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct panda_usb_can_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panda_usb_write_bulk_callback ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * usb_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct panda_usb_ctx*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static netdev_tx_t panda_usb_xmit(struct panda_inf_priv *priv,
				  struct panda_usb_can_msg *usb_msg,
				  struct panda_usb_ctx *ctx)
{
  struct urb *urb;
  u8 *buf;
  int err;

  /* create a URB, and a buffer for it, and copy the data to the URB */
  urb = usb_alloc_urb(0, GFP_ATOMIC);
  if (!urb)
    return -ENOMEM;

  buf = usb_alloc_coherent(priv->priv_dev->udev,
			   PANDA_USB_TX_BUFF_SIZE, GFP_ATOMIC,
			   &urb->transfer_dma);
  if (!buf) {
    err = -ENOMEM;
    goto nomembuf;
  }

  memcpy(buf, usb_msg, PANDA_USB_TX_BUFF_SIZE);

  usb_fill_bulk_urb(urb, priv->priv_dev->udev,
		    usb_sndbulkpipe(priv->priv_dev->udev, 3), buf,
		    PANDA_USB_TX_BUFF_SIZE, panda_usb_write_bulk_callback,
		    ctx);

  urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
  usb_anchor_urb(urb, &priv->tx_submitted);

  err = usb_submit_urb(urb, GFP_ATOMIC);
  if (unlikely(err))
    goto failed;

  /* Release our reference to this URB, the USB core will eventually free it entirely. */
  usb_free_urb(urb);

  return 0;

 failed:
  usb_unanchor_urb(urb);
  usb_free_coherent(priv->priv_dev->udev, PANDA_USB_TX_BUFF_SIZE, buf, urb->transfer_dma);

  if (err == -ENODEV)
    netif_device_detach(priv->netdev);
  else
    netdev_warn(priv->netdev, "failed tx_urb %d\n", err);

 nomembuf:
  usb_free_urb(urb);

  return err;
}