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
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct macsec_dev {int /*<<< orphan*/  real_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 struct macsec_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void macsec_encrypt_finish(struct sk_buff *skb, struct net_device *dev)
{
	struct macsec_dev *macsec = netdev_priv(dev);

	skb->dev = macsec->real_dev;
	skb_reset_mac_header(skb);
	skb->protocol = eth_hdr(skb)->h_proto;
}