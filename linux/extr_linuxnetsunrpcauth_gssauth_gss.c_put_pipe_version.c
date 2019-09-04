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
struct sunrpc_net {int pipe_version; int /*<<< orphan*/  pipe_users; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_version_lock ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static void put_pipe_version(struct net *net)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	if (atomic_dec_and_lock(&sn->pipe_users, &pipe_version_lock)) {
		sn->pipe_version = -1;
		spin_unlock(&pipe_version_lock);
	}
}