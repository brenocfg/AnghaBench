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
struct qeth_ipaddr {int dummy; } ;
struct qeth_card {int /*<<< orphan*/  ip_lock; } ;

/* Variables and functions */
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  qeth_l3_add_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  qeth_l3_delete_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_l3_handle_ip_event(struct qeth_card *card,
				   struct qeth_ipaddr *addr,
				   unsigned long event)
{
	switch (event) {
	case NETDEV_UP:
		spin_lock_bh(&card->ip_lock);
		qeth_l3_add_ip(card, addr);
		spin_unlock_bh(&card->ip_lock);
		return NOTIFY_OK;
	case NETDEV_DOWN:
		spin_lock_bh(&card->ip_lock);
		qeth_l3_delete_ip(card, addr);
		spin_unlock_bh(&card->ip_lock);
		return NOTIFY_OK;
	default:
		return NOTIFY_DONE;
	}
}