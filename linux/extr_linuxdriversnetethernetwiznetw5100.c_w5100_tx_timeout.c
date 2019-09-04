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
struct w5100_priv {int /*<<< orphan*/  restart_work; TYPE_1__* ops; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ may_sleep; } ;

/* Variables and functions */
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w5100_restart (struct net_device*) ; 

__attribute__((used)) static void w5100_tx_timeout(struct net_device *ndev)
{
	struct w5100_priv *priv = netdev_priv(ndev);

	if (priv->ops->may_sleep)
		schedule_work(&priv->restart_work);
	else
		w5100_restart(ndev);
}