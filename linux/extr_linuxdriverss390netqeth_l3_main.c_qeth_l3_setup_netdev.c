#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct qeth_hdr {int dummy; } ;
struct TYPE_9__ {scalar_t__* hsuid; } ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ link_type; int unique_id; int /*<<< orphan*/  guestlan; } ;
struct qeth_card {TYPE_3__* dev; int /*<<< orphan*/  napi; TYPE_2__ options; TYPE_1__ info; } ;
struct TYPE_10__ {int dev_id; int features; int hw_features; int vlan_features; int /*<<< orphan*/ * netdev_ops; scalar_t__ needed_headroom; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IPA_OUTBOUND_CHECKSUM_V6 ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int PAGE_SIZE ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
 scalar_t__ QETH_CARD_TYPE_OSD ; 
 scalar_t__ QETH_CARD_TYPE_OSX ; 
 scalar_t__ QETH_LINK_TYPE_HSTR ; 
 scalar_t__ QETH_LINK_TYPE_LANE_TR ; 
 int QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_NAPI_WEIGHT ; 
 int UNIQUE_ID_NOT_BY_CARD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  netif_keep_dst (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_napi_add (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_gso_max_size (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ qeth_is_supported6 (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_ethtool_ops ; 
 int /*<<< orphan*/  qeth_l3_get_unique_id (struct qeth_card*) ; 
 int qeth_l3_iqd_read_initial_mac (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_netdev_ops ; 
 int /*<<< orphan*/  qeth_l3_osa_netdev_ops ; 
 scalar_t__ qeth_netdev_is_registered (TYPE_3__*) ; 
 int /*<<< orphan*/  qeth_poll ; 
 int register_netdev (TYPE_3__*) ; 

__attribute__((used)) static int qeth_l3_setup_netdev(struct qeth_card *card)
{
	int rc;

	if (qeth_netdev_is_registered(card->dev))
		return 0;

	if (card->info.type == QETH_CARD_TYPE_OSD ||
	    card->info.type == QETH_CARD_TYPE_OSX) {
		if ((card->info.link_type == QETH_LINK_TYPE_LANE_TR) ||
		    (card->info.link_type == QETH_LINK_TYPE_HSTR)) {
			pr_info("qeth_l3: ignoring TR device\n");
			return -ENODEV;
		}

		card->dev->netdev_ops = &qeth_l3_osa_netdev_ops;

		/*IPv6 address autoconfiguration stuff*/
		qeth_l3_get_unique_id(card);
		if (!(card->info.unique_id & UNIQUE_ID_NOT_BY_CARD))
			card->dev->dev_id = card->info.unique_id & 0xffff;

		if (!card->info.guestlan) {
			card->dev->features |= NETIF_F_SG;
			card->dev->hw_features |= NETIF_F_TSO |
				NETIF_F_RXCSUM | NETIF_F_IP_CSUM;
			card->dev->vlan_features |= NETIF_F_TSO |
				NETIF_F_RXCSUM | NETIF_F_IP_CSUM;
		}

		if (qeth_is_supported6(card, IPA_OUTBOUND_CHECKSUM_V6)) {
			card->dev->hw_features |= NETIF_F_IPV6_CSUM;
			card->dev->vlan_features |= NETIF_F_IPV6_CSUM;
		}
	} else if (card->info.type == QETH_CARD_TYPE_IQD) {
		card->dev->flags |= IFF_NOARP;
		card->dev->netdev_ops = &qeth_l3_netdev_ops;

		rc = qeth_l3_iqd_read_initial_mac(card);
		if (rc)
			goto out;

		if (card->options.hsuid[0])
			memcpy(card->dev->perm_addr, card->options.hsuid, 9);
	} else
		return -ENODEV;

	card->dev->ethtool_ops = &qeth_l3_ethtool_ops;
	card->dev->needed_headroom = sizeof(struct qeth_hdr) - ETH_HLEN;
	card->dev->features |=	NETIF_F_HW_VLAN_CTAG_TX |
				NETIF_F_HW_VLAN_CTAG_RX |
				NETIF_F_HW_VLAN_CTAG_FILTER;

	netif_keep_dst(card->dev);
	if (card->dev->hw_features & NETIF_F_TSO)
		netif_set_gso_max_size(card->dev,
				       PAGE_SIZE * (QETH_MAX_BUFFER_ELEMENTS(card) - 1));

	netif_napi_add(card->dev, &card->napi, qeth_poll, QETH_NAPI_WEIGHT);
	rc = register_netdev(card->dev);
out:
	if (rc)
		card->dev->netdev_ops = NULL;
	return rc;
}