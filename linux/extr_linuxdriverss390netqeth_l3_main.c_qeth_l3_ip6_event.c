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
struct TYPE_4__ {int /*<<< orphan*/  pfxlen; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__ a6; } ;
struct qeth_ipaddr {TYPE_2__ u; } ;
struct qeth_card {int dummy; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct inet6_ifaddr {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; TYPE_3__* idev; } ;
struct TYPE_6__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_IPV6 ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_IP_TYPE_NORMAL ; 
 int /*<<< orphan*/  QETH_PROT_IPV6 ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 struct qeth_card* qeth_l3_get_card_from_dev (struct net_device*) ; 
 int qeth_l3_handle_ip_event (struct qeth_card*,struct qeth_ipaddr*,unsigned long) ; 
 int /*<<< orphan*/  qeth_l3_init_ipaddr (struct qeth_ipaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_ip6_event(struct notifier_block *this,
			     unsigned long event, void *ptr)
{
	struct inet6_ifaddr *ifa = (struct inet6_ifaddr *)ptr;
	struct net_device *dev = ifa->idev->dev;
	struct qeth_ipaddr addr;
	struct qeth_card *card;

	card = qeth_l3_get_card_from_dev(dev);
	if (!card)
		return NOTIFY_DONE;
	QETH_CARD_TEXT(card, 3, "ip6event");
	if (!qeth_is_supported(card, IPA_IPV6))
		return NOTIFY_DONE;

	qeth_l3_init_ipaddr(&addr, QETH_IP_TYPE_NORMAL, QETH_PROT_IPV6);
	addr.u.a6.addr = ifa->addr;
	addr.u.a6.pfxlen = ifa->prefix_len;

	return qeth_l3_handle_ip_event(card, &addr, event);
}