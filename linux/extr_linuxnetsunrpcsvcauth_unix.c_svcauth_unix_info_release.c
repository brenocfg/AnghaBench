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
struct svc_xprt {int /*<<< orphan*/  xpt_net; struct ip_map* xpt_auth_cache; } ;
struct sunrpc_net {int /*<<< orphan*/  ip_map_cache; } ;
struct ip_map {int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sunrpc_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

void
svcauth_unix_info_release(struct svc_xprt *xpt)
{
	struct ip_map *ipm;

	ipm = xpt->xpt_auth_cache;
	if (ipm != NULL) {
		struct sunrpc_net *sn;

		sn = net_generic(xpt->xpt_net, sunrpc_net_id);
		cache_put(&ipm->h, sn->ip_map_cache);
	}
}