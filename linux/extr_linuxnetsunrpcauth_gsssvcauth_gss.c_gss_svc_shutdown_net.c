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
 int /*<<< orphan*/  destroy_use_gss_proxy_proc_entry (struct net*) ; 
 int /*<<< orphan*/  rsc_cache_destroy_net (struct net*) ; 
 int /*<<< orphan*/  rsi_cache_destroy_net (struct net*) ; 

void
gss_svc_shutdown_net(struct net *net)
{
	destroy_use_gss_proxy_proc_entry(net);
	rsi_cache_destroy_net(net);
	rsc_cache_destroy_net(net);
}