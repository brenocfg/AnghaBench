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
typedef  int u32 ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  priority; scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct hdlc_header {int dummy; } ;
struct cisco_packet {void* time; int /*<<< orphan*/  rel; void* par2; void* par1; void* type; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CISCO_KEEPALIVE ; 
 int HZ ; 
 int INITIAL_JIFFIES ; 
 int /*<<< orphan*/  TC_PRIO_CONTROL ; 
 int /*<<< orphan*/  cisco_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 void* htonl (int) ; 
 int jiffies ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static void cisco_keepalive_send(struct net_device *dev, u32 type,
				 __be32 par1, __be32 par2)
{
	struct sk_buff *skb;
	struct cisco_packet *data;

	skb = dev_alloc_skb(sizeof(struct hdlc_header) +
			    sizeof(struct cisco_packet));
	if (!skb) {
		netdev_warn(dev, "Memory squeeze on cisco_keepalive_send()\n");
		return;
	}
	skb_reserve(skb, 4);
	cisco_hard_header(skb, dev, CISCO_KEEPALIVE, NULL, NULL, 0);
	data = (struct cisco_packet*)(skb->data + 4);

	data->type = htonl(type);
	data->par1 = par1;
	data->par2 = par2;
	data->rel = cpu_to_be16(0xFFFF);
	/* we will need do_div here if 1000 % HZ != 0 */
	data->time = htonl((jiffies - INITIAL_JIFFIES) * (1000 / HZ));

	skb_put(skb, sizeof(struct cisco_packet));
	skb->priority = TC_PRIO_CONTROL;
	skb->dev = dev;
	skb_reset_network_header(skb);

	dev_queue_xmit(skb);
}