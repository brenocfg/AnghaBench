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
struct TYPE_3__ {int* range; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ ip_local_ports; } ;
struct net {TYPE_2__ ipv4; } ;

/* Variables and functions */
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 

void inet_get_local_port_range(struct net *net, int *low, int *high)
{
	unsigned int seq;

	do {
		seq = read_seqbegin(&net->ipv4.ip_local_ports.lock);

		*low = net->ipv4.ip_local_ports.range[0];
		*high = net->ipv4.ip_local_ports.range[1];
	} while (read_seqretry(&net->ipv4.ip_local_ports.lock, seq));
}