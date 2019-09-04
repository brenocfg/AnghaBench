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
 int create_use_gss_proxy_proc_entry (struct net*) ; 
 int /*<<< orphan*/  destroy_use_gss_proxy_proc_entry (struct net*) ; 
 int rsc_cache_create_net (struct net*) ; 
 int /*<<< orphan*/  rsc_cache_destroy_net (struct net*) ; 
 int rsi_cache_create_net (struct net*) ; 

int
gss_svc_init_net(struct net *net)
{
	int rv;

	rv = rsc_cache_create_net(net);
	if (rv)
		return rv;
	rv = rsi_cache_create_net(net);
	if (rv)
		goto out1;
	rv = create_use_gss_proxy_proc_entry(net);
	if (rv)
		goto out2;
	return 0;
out2:
	destroy_use_gss_proxy_proc_entry(net);
out1:
	rsc_cache_destroy_net(net);
	return rv;
}