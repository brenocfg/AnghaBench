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
struct sk_buff {int dummy; } ;
struct panda_usb_can_msg {int bus_dat_len; int rir; int /*<<< orphan*/  data; } ;
struct panda_inf_priv {TYPE_1__* netdev; } ;
struct panda_dev_priv {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct can_frame {int can_id; scalar_t__ can_dlc; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int PANDA_CAN_EXTENDED ; 
 int PANDA_DLC_MASK ; 
 struct sk_buff* alloc_can_skb (TYPE_1__*,struct can_frame**) ; 
 scalar_t__ get_can_dlc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netif_device_present (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 struct panda_inf_priv* panda_get_inf_from_bus_id (struct panda_dev_priv*,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static void panda_usb_process_can_rx(struct panda_dev_priv *priv_dev,
				     struct panda_usb_can_msg *msg)
{
  struct can_frame *cf;
  struct sk_buff *skb;
  int bus_num;
  struct panda_inf_priv *priv_inf;
  struct net_device_stats *stats;

  bus_num = (msg->bus_dat_len >> 4) & 0xf;
  priv_inf = panda_get_inf_from_bus_id(priv_dev, bus_num);
  if(!priv_inf){
    printk("Got something on an unused interface %d\n", bus_num);
    return;
  }
  printk("Recv bus %d\n", bus_num);

  stats = &priv_inf->netdev->stats;
  //u16 sid;

  if (!netif_device_present(priv_inf->netdev))
    return;

  skb = alloc_can_skb(priv_inf->netdev, &cf);
  if (!skb)
    return;

  if(msg->rir & PANDA_CAN_EXTENDED){
    cf->can_id = (msg->rir >> 3) | CAN_EFF_FLAG;
  }else{
    cf->can_id = (msg->rir >> 21);
  }

  // TODO: Handle Remote Frames
  //if (msg->dlc & MCBA_DLC_RTR_MASK)
  //  cf->can_id |= CAN_RTR_FLAG;

  cf->can_dlc = get_can_dlc(msg->bus_dat_len & PANDA_DLC_MASK);

  memcpy(cf->data, msg->data, cf->can_dlc);

  stats->rx_packets++;
  stats->rx_bytes += cf->can_dlc;

  netif_rx(skb);
}