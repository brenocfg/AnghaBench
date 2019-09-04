#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * spy_data; } ;
struct wl3501_card {TYPE_2__ wireless_data; struct pcmcia_device* p_dev; int /*<<< orphan*/  spy_data; } ;
struct pcmcia_device {int config_index; struct net_device* priv; int /*<<< orphan*/  config_flags; TYPE_1__** resource; } ;
struct net_device {int watchdog_timeo; int /*<<< orphan*/ * wireless_handlers; TYPE_2__* wireless_data; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_3__ {int end; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_8 ; 
 struct net_device* alloc_etherdev (int) ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int wl3501_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  wl3501_handler_def ; 
 int /*<<< orphan*/  wl3501_netdev_ops ; 

__attribute__((used)) static int wl3501_probe(struct pcmcia_device *p_dev)
{
	struct net_device *dev;
	struct wl3501_card *this;

	/* The io structure describes IO port mapping */
	p_dev->resource[0]->end	= 16;
	p_dev->resource[0]->flags	= IO_DATA_PATH_WIDTH_8;

	/* General socket configuration */
	p_dev->config_flags	= CONF_ENABLE_IRQ;
	p_dev->config_index	= 1;

	dev = alloc_etherdev(sizeof(struct wl3501_card));
	if (!dev)
		goto out_link;


	dev->netdev_ops		= &wl3501_netdev_ops;
	dev->watchdog_timeo	= 5 * HZ;

	this = netdev_priv(dev);
	this->wireless_data.spy_data = &this->spy_data;
	this->p_dev = p_dev;
	dev->wireless_data	= &this->wireless_data;
	dev->wireless_handlers	= &wl3501_handler_def;
	netif_stop_queue(dev);
	p_dev->priv = dev;

	return wl3501_config(p_dev);
out_link:
	return -ENOMEM;
}