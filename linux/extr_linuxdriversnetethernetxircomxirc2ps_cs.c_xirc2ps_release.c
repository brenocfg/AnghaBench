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
struct pcmcia_device {struct net_device* priv; TYPE_1__** resource; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct local_info {scalar_t__ dingo_ccr; scalar_t__ dingo; } ;
struct TYPE_2__ {scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void
xirc2ps_release(struct pcmcia_device *link)
{
	dev_dbg(&link->dev, "release\n");

	if (link->resource[2]->end) {
		struct net_device *dev = link->priv;
		struct local_info *local = netdev_priv(dev);
		if (local->dingo)
			iounmap(local->dingo_ccr - 0x0800);
	}
	pcmcia_disable_device(link);
}