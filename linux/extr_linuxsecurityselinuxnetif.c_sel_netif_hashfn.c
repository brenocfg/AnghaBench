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
typedef  uintptr_t u32 ;
struct net {int dummy; } ;

/* Variables and functions */
 int SEL_NETIF_HASH_SIZE ; 

__attribute__((used)) static inline u32 sel_netif_hashfn(const struct net *ns, int ifindex)
{
	return (((uintptr_t)ns + ifindex) & (SEL_NETIF_HASH_SIZE - 1));
}