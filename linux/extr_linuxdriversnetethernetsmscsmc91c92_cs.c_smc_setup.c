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
struct pcmcia_device {int /*<<< orphan*/ * prod_id; struct net_device* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ cvt_ascii_address (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_get_mac_from_cis (struct pcmcia_device*,struct net_device*) ; 

__attribute__((used)) static int smc_setup(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;

    /* Check for a LAN function extension tuple */
    if (!pcmcia_get_mac_from_cis(link, dev))
	    return 0;

    /* Try the third string in the Version 1 Version/ID tuple. */
    if (link->prod_id[2]) {
	    if (cvt_ascii_address(dev, link->prod_id[2]) == 0)
		    return 0;
    }
    return -1;
}