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
struct TYPE_2__ {void* sysctl_udp_wmem_min; void* sysctl_udp_rmem_min; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 void* SK_MEM_QUANTUM ; 

__attribute__((used)) static void __udp_sysctl_init(struct net *net)
{
	net->ipv4.sysctl_udp_rmem_min = SK_MEM_QUANTUM;
	net->ipv4.sysctl_udp_wmem_min = SK_MEM_QUANTUM;

#ifdef CONFIG_NET_L3_MASTER_DEV
	net->ipv4.sysctl_udp_l3mdev_accept = 0;
#endif
}