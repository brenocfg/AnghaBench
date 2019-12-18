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
struct net {int dummy; } ;

/* Variables and functions */
 int nfs_dns_resolver_cache_init (struct net*) ; 

__attribute__((used)) static int nfs4_dns_net_init(struct net *net)
{
	return nfs_dns_resolver_cache_init(net);
}