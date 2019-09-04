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
struct qeth_card {int /*<<< orphan*/  dev; } ;
struct inet6_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_IPV6 ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 struct inet6_dev* in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_add_mc6_to_hash (struct qeth_card*,struct inet6_dev*) ; 
 int /*<<< orphan*/  qeth_l3_add_vlan_mc6 (struct qeth_card*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_l3_add_multicast_ipv6(struct qeth_card *card)
{
	struct inet6_dev *in6_dev;

	QETH_CARD_TEXT(card, 4, "chkmcv6");

	if (!qeth_is_supported(card, IPA_IPV6))
		return ;
	in6_dev = in6_dev_get(card->dev);
	if (!in6_dev)
		return;

	rcu_read_lock();
	read_lock_bh(&in6_dev->lock);
	qeth_l3_add_mc6_to_hash(card, in6_dev);
	qeth_l3_add_vlan_mc6(card);
	read_unlock_bh(&in6_dev->lock);
	rcu_read_unlock();
	in6_dev_put(in6_dev);
}