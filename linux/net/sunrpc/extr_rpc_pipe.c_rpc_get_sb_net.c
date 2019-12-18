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
struct super_block {int dummy; } ;
struct sunrpc_net {int /*<<< orphan*/  pipefs_sb_lock; struct super_block* pipefs_sb; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

struct super_block *rpc_get_sb_net(const struct net *net)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	mutex_lock(&sn->pipefs_sb_lock);
	if (sn->pipefs_sb)
		return sn->pipefs_sb;
	mutex_unlock(&sn->pipefs_sb_lock);
	return NULL;
}