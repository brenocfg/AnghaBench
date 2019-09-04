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
struct pcmcia_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISTPL_FUNCE ; 
 int /*<<< orphan*/  pcmcia_do_get_mac ; 
 int pcmcia_loop_tuple (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

int pcmcia_get_mac_from_cis(struct pcmcia_device *p_dev, struct net_device *dev)
{
	return pcmcia_loop_tuple(p_dev, CISTPL_FUNCE, pcmcia_do_get_mac, dev);
}