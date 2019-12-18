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
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t ipcaif_get_size(const struct net_device *dev)
{
	return
		/* IFLA_CAIF_IPV4_CONNID */
		nla_total_size(4) +
		/* IFLA_CAIF_IPV6_CONNID */
		nla_total_size(4) +
		/* IFLA_CAIF_LOOPBACK */
		nla_total_size(2) +
		0;
}