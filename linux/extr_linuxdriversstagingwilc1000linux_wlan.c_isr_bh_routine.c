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
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {scalar_t__ close; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (void*) ; 
 int /*<<< orphan*/  wilc_handle_isr (struct wilc*) ; 

__attribute__((used)) static irqreturn_t isr_bh_routine(int irq, void *userdata)
{
	struct net_device *dev = userdata;
	struct wilc_vif *vif = netdev_priv(userdata);
	struct wilc *wilc = vif->wilc;

	if (wilc->close) {
		netdev_err(dev, "Can't handle BH interrupt\n");
		return IRQ_HANDLED;
	}

	wilc_handle_isr(wilc);

	return IRQ_HANDLED;
}