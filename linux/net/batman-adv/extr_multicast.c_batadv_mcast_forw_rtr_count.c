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
struct TYPE_2__ {int /*<<< orphan*/  num_want_all_rtr6; int /*<<< orphan*/  num_want_all_rtr4; } ;
struct batadv_priv {TYPE_1__ mcast; } ;

/* Variables and functions */
#define  ETH_P_IP 129 
#define  ETH_P_IPV6 128 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int batadv_mcast_forw_rtr_count(struct batadv_priv *bat_priv,
				       int protocol)
{
	switch (protocol) {
	case ETH_P_IP:
		return atomic_read(&bat_priv->mcast.num_want_all_rtr4);
	case ETH_P_IPV6:
		return atomic_read(&bat_priv->mcast.num_want_all_rtr6);
	default:
		return 0;
	}
}