#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_3__ {scalar_t__ num_dev_open; int dev_enabled; int /*<<< orphan*/  pri_only; scalar_t__ no_pri; scalar_t__ hw_downloading; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRISM2_CALLBACK_ENABLE ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  prism2_callback (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int prism2_hw_enable (struct net_device*,int) ; 
 scalar_t__ prism2_hw_init (struct net_device*,int) ; 
 scalar_t__ prism2_hw_init2 (struct net_device*,int) ; 

__attribute__((used)) static int prism2_hw_config(struct net_device *dev, int initial)
{
	struct hostap_interface *iface;
	local_info_t *local;

	iface = netdev_priv(dev);
	local = iface->local;

	if (local->hw_downloading)
		return 1;

	if (prism2_hw_init(dev, initial)) {
		return local->no_pri ? 0 : 1;
	}

	if (prism2_hw_init2(dev, initial))
		return 1;

	/* Enable firmware if secondary image is loaded and at least one of the
	 * netdevices is up. */
	if (!local->pri_only &&
	    (initial == 0 || (initial == 2 && local->num_dev_open > 0))) {
		if (!local->dev_enabled)
			prism2_callback(local, PRISM2_CALLBACK_ENABLE);
		local->dev_enabled = 1;
		return prism2_hw_enable(dev, initial);
	}

	return 0;
}