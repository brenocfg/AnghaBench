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
struct pcmcia_device {int /*<<< orphan*/  open; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct local_info {struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct net_device*) ; 
 int /*<<< orphan*/  do_reset (struct net_device*,int) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 

__attribute__((used)) static int
do_open(struct net_device *dev)
{
    struct local_info *lp = netdev_priv(dev);
    struct pcmcia_device *link = lp->p_dev;

    dev_dbg(&link->dev, "do_open(%p)\n", dev);

    /* Check that the PCMCIA card is still here. */
    /* Physical device present signature. */
    if (!pcmcia_dev_present(link))
	return -ENODEV;

    /* okay */
    link->open++;

    netif_start_queue(dev);
    do_reset(dev,1);

    return 0;
}