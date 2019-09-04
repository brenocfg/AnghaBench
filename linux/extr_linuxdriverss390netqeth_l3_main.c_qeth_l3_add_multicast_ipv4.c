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
struct in_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 struct in_device* __in_dev_get_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_add_mc_to_hash (struct qeth_card*,struct in_device*) ; 
 int /*<<< orphan*/  qeth_l3_add_vlan_mc (struct qeth_card*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void qeth_l3_add_multicast_ipv4(struct qeth_card *card)
{
	struct in_device *in4_dev;

	QETH_CARD_TEXT(card, 4, "chkmcv4");

	rcu_read_lock();
	in4_dev = __in_dev_get_rcu(card->dev);
	if (in4_dev == NULL)
		goto unlock;
	qeth_l3_add_mc_to_hash(card, in4_dev);
	qeth_l3_add_vlan_mc(card);
unlock:
	rcu_read_unlock();
}