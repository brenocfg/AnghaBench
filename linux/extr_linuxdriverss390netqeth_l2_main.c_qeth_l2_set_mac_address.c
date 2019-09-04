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
struct sockaddr {int /*<<< orphan*/ * sa_data; } ;
struct TYPE_2__ {scalar_t__ type; int mac_bits; } ;
struct qeth_card {int /*<<< orphan*/  conf_mutex; TYPE_1__ info; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int ERESTARTSYS ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 scalar_t__ QETH_CARD_TYPE_OSM ; 
 scalar_t__ QETH_CARD_TYPE_OSN ; 
 scalar_t__ QETH_CARD_TYPE_OSX ; 
 int QETH_LAYER2_MAC_REGISTERED ; 
 int /*<<< orphan*/  QETH_RECOVER_THREAD ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_card_hw_is_reachable (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l2_remove_mac (struct qeth_card*,int /*<<< orphan*/ *) ; 
 int qeth_l2_send_setmac (struct qeth_card*,int /*<<< orphan*/ *) ; 
 scalar_t__ qeth_wait_for_threads (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l2_set_mac_address(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;
	struct qeth_card *card = dev->ml_priv;
	u8 old_addr[ETH_ALEN];
	int rc = 0;

	QETH_CARD_TEXT(card, 3, "setmac");

	if (card->info.type == QETH_CARD_TYPE_OSN ||
	    card->info.type == QETH_CARD_TYPE_OSM ||
	    card->info.type == QETH_CARD_TYPE_OSX) {
		QETH_CARD_TEXT(card, 3, "setmcTYP");
		return -EOPNOTSUPP;
	}
	QETH_CARD_HEX(card, 3, addr->sa_data, ETH_ALEN);
	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (qeth_wait_for_threads(card, QETH_RECOVER_THREAD)) {
		QETH_CARD_TEXT(card, 3, "setmcREC");
		return -ERESTARTSYS;
	}

	/* avoid racing against concurrent state change: */
	if (!mutex_trylock(&card->conf_mutex))
		return -EAGAIN;

	if (!qeth_card_hw_is_reachable(card)) {
		ether_addr_copy(dev->dev_addr, addr->sa_data);
		goto out_unlock;
	}

	/* don't register the same address twice */
	if (ether_addr_equal_64bits(dev->dev_addr, addr->sa_data) &&
	    (card->info.mac_bits & QETH_LAYER2_MAC_REGISTERED))
		goto out_unlock;

	/* add the new address, switch over, drop the old */
	rc = qeth_l2_send_setmac(card, addr->sa_data);
	if (rc)
		goto out_unlock;
	ether_addr_copy(old_addr, dev->dev_addr);
	ether_addr_copy(dev->dev_addr, addr->sa_data);

	if (card->info.mac_bits & QETH_LAYER2_MAC_REGISTERED)
		qeth_l2_remove_mac(card, old_addr);
	card->info.mac_bits |= QETH_LAYER2_MAC_REGISTERED;

out_unlock:
	mutex_unlock(&card->conf_mutex);
	return rc;
}