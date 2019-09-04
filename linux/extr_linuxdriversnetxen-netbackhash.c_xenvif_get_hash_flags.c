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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ alg; } ;
struct xenvif {TYPE_1__ hash; } ;

/* Variables and functions */
 scalar_t__ XEN_NETIF_CTRL_HASH_ALGORITHM_NONE ; 
 int XEN_NETIF_CTRL_HASH_TYPE_IPV4 ; 
 int XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP ; 
 int XEN_NETIF_CTRL_HASH_TYPE_IPV6 ; 
 int XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP ; 
 int XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED ; 
 int XEN_NETIF_CTRL_STATUS_SUCCESS ; 

u32 xenvif_get_hash_flags(struct xenvif *vif, u32 *flags)
{
	if (vif->hash.alg == XEN_NETIF_CTRL_HASH_ALGORITHM_NONE)
		return XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED;

	*flags = XEN_NETIF_CTRL_HASH_TYPE_IPV4 |
		 XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP |
		 XEN_NETIF_CTRL_HASH_TYPE_IPV6 |
		 XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP;

	return XEN_NETIF_CTRL_STATUS_SUCCESS;
}