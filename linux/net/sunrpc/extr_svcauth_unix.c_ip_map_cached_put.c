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
struct svc_xprt {int /*<<< orphan*/  xpt_net; int /*<<< orphan*/  xpt_lock; struct ip_map* xpt_auth_cache; int /*<<< orphan*/  xpt_flags; } ;
struct sunrpc_net {int /*<<< orphan*/  ip_map_cache; } ;
struct ip_map {int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPT_CACHE_AUTH ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sunrpc_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ip_map_cached_put(struct svc_xprt *xprt, struct ip_map *ipm)
{
	if (test_bit(XPT_CACHE_AUTH, &xprt->xpt_flags)) {
		spin_lock(&xprt->xpt_lock);
		if (xprt->xpt_auth_cache == NULL) {
			/* newly cached, keep the reference */
			xprt->xpt_auth_cache = ipm;
			ipm = NULL;
		}
		spin_unlock(&xprt->xpt_lock);
	}
	if (ipm) {
		struct sunrpc_net *sn;

		sn = net_generic(xprt->xpt_net, sunrpc_net_id);
		cache_put(&ipm->h, sn->ip_map_cache);
	}
}