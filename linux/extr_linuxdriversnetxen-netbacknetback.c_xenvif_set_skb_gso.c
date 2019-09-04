#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xenvif {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int type; scalar_t__ size; } ;
struct TYPE_4__ {TYPE_2__ gso; } ;
struct xen_netif_extra_info {TYPE_1__ u; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ gso_size; int /*<<< orphan*/  gso_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SKB_GSO_TCPV4 ; 
 int /*<<< orphan*/  SKB_GSO_TCPV6 ; 
#define  XEN_NETIF_GSO_TYPE_TCPV4 129 
#define  XEN_NETIF_GSO_TYPE_TCPV6 128 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  xenvif_fatal_tx_err (struct xenvif*) ; 

__attribute__((used)) static int xenvif_set_skb_gso(struct xenvif *vif,
			      struct sk_buff *skb,
			      struct xen_netif_extra_info *gso)
{
	if (!gso->u.gso.size) {
		netdev_err(vif->dev, "GSO size must not be zero.\n");
		xenvif_fatal_tx_err(vif);
		return -EINVAL;
	}

	switch (gso->u.gso.type) {
	case XEN_NETIF_GSO_TYPE_TCPV4:
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
		break;
	case XEN_NETIF_GSO_TYPE_TCPV6:
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
		break;
	default:
		netdev_err(vif->dev, "Bad GSO type %d.\n", gso->u.gso.type);
		xenvif_fatal_tx_err(vif);
		return -EINVAL;
	}

	skb_shinfo(skb)->gso_size = gso->u.gso.size;
	/* gso_segs will be calculated later */

	return 0;
}