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
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  dev; struct panda_usb_ctx* context; } ;
struct panda_usb_ctx {int /*<<< orphan*/  ndx; scalar_t__ dlc; TYPE_2__* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_4__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  panda_usb_free_ctx (struct panda_usb_ctx*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panda_usb_write_bulk_callback(struct urb *urb)
{
  struct panda_usb_ctx *ctx = urb->context;
  struct net_device *netdev;

  WARN_ON(!ctx);

  netdev = ctx->priv->netdev;

  /* free up our allocated buffer */
  usb_free_coherent(urb->dev, urb->transfer_buffer_length,
		    urb->transfer_buffer, urb->transfer_dma);

  if (!netif_device_present(netdev))
    return;

  netdev->stats.tx_packets++;
  netdev->stats.tx_bytes += ctx->dlc;

  can_get_echo_skb(netdev, ctx->ndx);

  if (urb->status)
    netdev_info(netdev, "Tx URB aborted (%d)\n", urb->status);

  /* Release the context */
  panda_usb_free_ctx(ctx);
}