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
struct TYPE_4__ {int /*<<< orphan*/  nr_firstnet; int /*<<< orphan*/  nr_lastnet; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_net; } ;
struct atalk_iface {TYPE_2__ nets; TYPE_1__ address; } ;
struct atalk_addr {int s_node; int /*<<< orphan*/  s_net; } ;

/* Variables and functions */
 int ATADDR_ANYNET ; 
 int ATADDR_ANYNODE ; 
 int EADDRINUSE ; 
 int aarp_proxy_probe_network (struct atalk_iface*,struct atalk_addr*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int jiffies ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atif_proxy_probe_device(struct atalk_iface *atif,
				   struct atalk_addr *proxy_addr)
{
	int netrange = ntohs(atif->nets.nr_lastnet) -
			ntohs(atif->nets.nr_firstnet) + 1;
	/* we probe the interface's network */
	int probe_net = ntohs(atif->address.s_net);
	int probe_node = ATADDR_ANYNODE;	    /* we'll take anything */
	int netct, nodect;

	/* Offset the network we start probing with */
	if (probe_net == ATADDR_ANYNET) {
		probe_net = ntohs(atif->nets.nr_firstnet);
		if (netrange)
			probe_net += jiffies % netrange;
	}

	if (probe_node == ATADDR_ANYNODE)
		probe_node = jiffies & 0xFF;

	/* Scan the networks */
	for (netct = 0; netct <= netrange; netct++) {
		/* Sweep the available nodes from a given start */
		proxy_addr->s_net = htons(probe_net);
		for (nodect = 0; nodect < 256; nodect++) {
			proxy_addr->s_node = (nodect + probe_node) & 0xFF;
			if (proxy_addr->s_node > 0 &&
			    proxy_addr->s_node < 254) {
				/* Tell AARP to probe a proposed address */
				int ret = aarp_proxy_probe_network(atif,
								    proxy_addr);

				if (ret != -EADDRINUSE)
					return ret;
			}
		}
		probe_net++;
		if (probe_net > ntohs(atif->nets.nr_lastnet))
			probe_net = ntohs(atif->nets.nr_firstnet);
	}

	return -EADDRINUSE;	/* Network is full... */
}