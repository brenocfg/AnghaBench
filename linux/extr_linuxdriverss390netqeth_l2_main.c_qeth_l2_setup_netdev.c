#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qeth_hdr {int dummy; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  guestlan; } ;
struct qeth_card {TYPE_2__* dev; int /*<<< orphan*/  napi; TYPE_1__ info; } ;
struct TYPE_6__ {int needed_headroom; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  vlan_features; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  features; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  IPA_INBOUND_CHECKSUM ; 
 int /*<<< orphan*/  IPA_INBOUND_CHECKSUM_V6 ; 
 int /*<<< orphan*/  IPA_OUTBOUND_CHECKSUM ; 
 int /*<<< orphan*/  IPA_OUTBOUND_CHECKSUM_V6 ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int /*<<< orphan*/  NETIF_F_IPV6_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 int /*<<< orphan*/  NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  NETIF_F_SG ; 
 int /*<<< orphan*/  NETIF_F_VLAN_CHALLENGED ; 
 scalar_t__ QETH_CARD_TYPE_OSD ; 
 scalar_t__ QETH_CARD_TYPE_OSM ; 
 scalar_t__ QETH_CARD_TYPE_OSN ; 
 int /*<<< orphan*/  QETH_NAPI_WEIGHT ; 
 int /*<<< orphan*/  netif_napi_add (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_is_supported6 (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l2_ethtool_ops ; 
 int /*<<< orphan*/  qeth_l2_netdev_ops ; 
 int /*<<< orphan*/  qeth_l2_osn_ops ; 
 int /*<<< orphan*/  qeth_l2_request_initial_mac (struct qeth_card*) ; 
 scalar_t__ qeth_netdev_is_registered (TYPE_2__*) ; 
 int /*<<< orphan*/  qeth_poll ; 
 int register_netdev (TYPE_2__*) ; 

__attribute__((used)) static int qeth_l2_setup_netdev(struct qeth_card *card)
{
	int rc;

	if (qeth_netdev_is_registered(card->dev))
		return 0;

	card->dev->priv_flags |= IFF_UNICAST_FLT;
	card->dev->netdev_ops = &qeth_l2_netdev_ops;
	if (card->info.type == QETH_CARD_TYPE_OSN) {
		card->dev->ethtool_ops = &qeth_l2_osn_ops;
		card->dev->flags |= IFF_NOARP;
	} else {
		card->dev->ethtool_ops = &qeth_l2_ethtool_ops;
		card->dev->needed_headroom = sizeof(struct qeth_hdr);
	}

	if (card->info.type == QETH_CARD_TYPE_OSM)
		card->dev->features |= NETIF_F_VLAN_CHALLENGED;
	else
		card->dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	if (card->info.type == QETH_CARD_TYPE_OSD && !card->info.guestlan) {
		card->dev->features |= NETIF_F_SG;
		/* OSA 3S and earlier has no RX/TX support */
		if (qeth_is_supported(card, IPA_OUTBOUND_CHECKSUM)) {
			card->dev->hw_features |= NETIF_F_IP_CSUM;
			card->dev->vlan_features |= NETIF_F_IP_CSUM;
		}
	}
	if (qeth_is_supported6(card, IPA_OUTBOUND_CHECKSUM_V6)) {
		card->dev->hw_features |= NETIF_F_IPV6_CSUM;
		card->dev->vlan_features |= NETIF_F_IPV6_CSUM;
	}
	if (qeth_is_supported(card, IPA_INBOUND_CHECKSUM) ||
	    qeth_is_supported6(card, IPA_INBOUND_CHECKSUM_V6)) {
		card->dev->hw_features |= NETIF_F_RXCSUM;
		card->dev->vlan_features |= NETIF_F_RXCSUM;
	}

	qeth_l2_request_initial_mac(card);
	netif_napi_add(card->dev, &card->napi, qeth_poll, QETH_NAPI_WEIGHT);
	rc = register_netdev(card->dev);
	if (rc)
		card->dev->netdev_ops = NULL;
	return rc;
}