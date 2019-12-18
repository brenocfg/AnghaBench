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
struct sunrpc_net {int /*<<< orphan*/  pipefs_sb_lock; int /*<<< orphan*/ * pipefs_sb; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

void rpc_put_sb_net(const struct net *net)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	WARN_ON(sn->pipefs_sb == NULL);
	mutex_unlock(&sn->pipefs_sb_lock);
}