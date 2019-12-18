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
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct bcm_sock {TYPE_1__ notifier; int /*<<< orphan*/  rx_ops; int /*<<< orphan*/  tx_ops; int /*<<< orphan*/ * bcm_proc_read; scalar_t__ dropped_usr_msgs; scalar_t__ ifindex; scalar_t__ bound; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcm_notifier ; 
 struct bcm_sock* bcm_sk (struct sock*) ; 
 int /*<<< orphan*/  register_netdevice_notifier (TYPE_1__*) ; 

__attribute__((used)) static int bcm_init(struct sock *sk)
{
	struct bcm_sock *bo = bcm_sk(sk);

	bo->bound            = 0;
	bo->ifindex          = 0;
	bo->dropped_usr_msgs = 0;
	bo->bcm_proc_read    = NULL;

	INIT_LIST_HEAD(&bo->tx_ops);
	INIT_LIST_HEAD(&bo->rx_ops);

	/* set notifier */
	bo->notifier.notifier_call = bcm_notifier;

	register_netdevice_notifier(&bo->notifier);

	return 0;
}