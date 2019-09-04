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
struct TYPE_2__ {scalar_t__ clock_type; scalar_t__ loopback; } ;
typedef  TYPE_1__ sync_serial_settings ;
struct net_device {int dummy; } ;
struct dscc4_dev_priv {TYPE_1__ settings; } ;

/* Variables and functions */
 scalar_t__ CLOCK_INT ; 
 struct net_device* dscc4_to_dev (struct dscc4_dev_priv*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 

__attribute__((used)) static int dscc4_loopback_check(struct dscc4_dev_priv *dpriv)
{
	sync_serial_settings *settings = &dpriv->settings;

	if (settings->loopback && (settings->clock_type != CLOCK_INT)) {
		struct net_device *dev = dscc4_to_dev(dpriv);

		netdev_info(dev, "loopback requires clock\n");
		return -1;
	}
	return 0;
}