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
struct qeth_card {scalar_t__ state; } ;
struct net_device {struct qeth_card* ml_priv; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
typedef  int /*<<< orphan*/  features ;

/* Variables and functions */
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_RECOVER ; 
 int /*<<< orphan*/  IPA_INBOUND_CHECKSUM ; 
 int /*<<< orphan*/  IPA_INBOUND_CHECKSUM_V6 ; 
 int /*<<< orphan*/  IPA_OUTBOUND_CHECKSUM ; 
 int /*<<< orphan*/  IPA_OUTBOUND_CHECKSUM_V6 ; 
 int /*<<< orphan*/  IPA_OUTBOUND_TSO ; 
 int /*<<< orphan*/  NETIF_F_IPV6_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 int /*<<< orphan*/  NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  NETIF_F_TSO ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_HW_FEATURES ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_is_supported6 (struct qeth_card*,int /*<<< orphan*/ ) ; 

netdev_features_t qeth_fix_features(struct net_device *dev,
				    netdev_features_t features)
{
	struct qeth_card *card = dev->ml_priv;

	QETH_DBF_TEXT(SETUP, 2, "fixfeat");
	if (!qeth_is_supported(card, IPA_OUTBOUND_CHECKSUM))
		features &= ~NETIF_F_IP_CSUM;
	if (!qeth_is_supported6(card, IPA_OUTBOUND_CHECKSUM_V6))
		features &= ~NETIF_F_IPV6_CSUM;
	if (!qeth_is_supported(card, IPA_INBOUND_CHECKSUM) &&
	    !qeth_is_supported6(card, IPA_INBOUND_CHECKSUM_V6))
		features &= ~NETIF_F_RXCSUM;
	if (!qeth_is_supported(card, IPA_OUTBOUND_TSO))
		features &= ~NETIF_F_TSO;
	/* if the card isn't up, remove features that require hw changes */
	if (card->state == CARD_STATE_DOWN ||
	    card->state == CARD_STATE_RECOVER)
		features &= ~QETH_HW_FEATURES;
	QETH_DBF_HEX(SETUP, 2, &features, sizeof(features));
	return features;
}