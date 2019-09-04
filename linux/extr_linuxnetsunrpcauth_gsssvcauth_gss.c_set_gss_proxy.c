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
struct sunrpc_net {int /*<<< orphan*/  use_gss_proxy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static int set_gss_proxy(struct net *net, int type)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	int ret;

	WARN_ON_ONCE(type != 0 && type != 1);
	ret = cmpxchg(&sn->use_gss_proxy, -1, type);
	if (ret != -1 && ret != type)
		return -EBUSY;
	return 0;
}