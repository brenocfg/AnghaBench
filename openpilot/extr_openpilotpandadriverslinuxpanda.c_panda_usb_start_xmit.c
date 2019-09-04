#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct panda_usb_ctx {int /*<<< orphan*/  ndx; } ;
struct panda_usb_can_msg {int /*<<< orphan*/  data; void* bus_dat_len; void* rir; } ;
struct panda_inf_priv {int mcu_can_ifnum; TYPE_1__* netdev; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int dummy; } ;
struct can_frame {int can_id; int can_dlc; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_3__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int PANDA_CAN_EXTENDED ; 
 int PANDA_CAN_TRANSMIT ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_free_echo_skb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,int) ; 
 struct panda_inf_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  panda_usb_free_ctx (struct panda_usb_ctx*) ; 
 struct panda_usb_ctx* panda_usb_get_free_ctx (struct panda_inf_priv*,struct can_frame*) ; 
 int panda_usb_xmit (struct panda_inf_priv*,struct panda_usb_can_msg*,struct panda_usb_ctx*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static netdev_tx_t panda_usb_start_xmit(struct sk_buff *skb,
					struct net_device *netdev)
{
  struct panda_inf_priv *priv_inf = netdev_priv(netdev);
  struct can_frame *cf = (struct can_frame *)skb->data;
  struct panda_usb_ctx *ctx = NULL;
  struct net_device_stats *stats = &priv_inf->netdev->stats;
  int err;
  struct panda_usb_can_msg usb_msg = {};
  int bus = priv_inf->mcu_can_ifnum;

  if (can_dropped_invalid_skb(netdev, skb)){
    printk("Invalid CAN packet");
    return NETDEV_TX_OK;
  }

  ctx = panda_usb_get_free_ctx(priv_inf, cf);

  //Warning: cargo cult. Can't tell what this is for, but it is
  //everywhere and encouraged in the documentation.
  can_put_echo_skb(skb, priv_inf->netdev, ctx->ndx);

  if(cf->can_id & CAN_EFF_FLAG){
    usb_msg.rir = cpu_to_le32(((cf->can_id & 0x1FFFFFFF) << 3) |
			      PANDA_CAN_TRANSMIT | PANDA_CAN_EXTENDED);
  }else{
    usb_msg.rir = cpu_to_le32(((cf->can_id & 0x7FF) << 21) | PANDA_CAN_TRANSMIT);
  }
  usb_msg.bus_dat_len = cpu_to_le32((cf->can_dlc & 0x0F) | (bus << 4));

  memcpy(usb_msg.data, cf->data, cf->can_dlc);

  //TODO Handle Remote Frames
  //if (cf->can_id & CAN_RTR_FLAG)
  //  usb_msg.dlc |= PANDA_DLC_RTR_MASK;

  netdev_err(netdev, "Received data from socket. canid: %x; len: %d\n", cf->can_id, cf->can_dlc);

  err = panda_usb_xmit(priv_inf, &usb_msg, ctx);
  if (err)
    goto xmit_failed;

  return NETDEV_TX_OK;

 xmit_failed:
  can_free_echo_skb(priv_inf->netdev, ctx->ndx);
  panda_usb_free_ctx(ctx);
  dev_kfree_skb(skb);
  stats->tx_dropped++;

  return NETDEV_TX_OK;
}