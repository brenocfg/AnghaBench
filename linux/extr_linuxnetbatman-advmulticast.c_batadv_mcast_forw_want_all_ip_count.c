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
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_want_all_ipv6; int /*<<< orphan*/  num_want_all_ipv4; } ;
struct batadv_priv {TYPE_1__ mcast; } ;

/* Variables and functions */
#define  ETH_P_IP 129 
#define  ETH_P_IPV6 128 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int batadv_mcast_forw_want_all_ip_count(struct batadv_priv *bat_priv,
					       struct ethhdr *ethhdr)
{
	switch (ntohs(ethhdr->h_proto)) {
	case ETH_P_IP:
		return atomic_read(&bat_priv->mcast.num_want_all_ipv4);
	case ETH_P_IPV6:
		return atomic_read(&bat_priv->mcast.num_want_all_ipv6);
	default:
		/* we shouldn't be here... */
		return 0;
	}
}