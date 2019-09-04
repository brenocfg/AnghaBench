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
struct r8192_priv {scalar_t__ irq_enabled; TYPE_1__* ops; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_disable ) (struct net_device*) ;} ;

/* Variables and functions */
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

void rtl92e_irq_disable(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	priv->ops->irq_disable(dev);

	priv->irq_enabled = 0;
}