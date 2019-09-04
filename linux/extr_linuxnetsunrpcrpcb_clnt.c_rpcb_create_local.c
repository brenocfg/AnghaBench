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
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpcb_create_local_net (struct net*) ; 
 scalar_t__ rpcb_create_local_unix (struct net*) ; 
 scalar_t__ rpcb_get_local (struct net*) ; 

int rpcb_create_local(struct net *net)
{
	static DEFINE_MUTEX(rpcb_create_local_mutex);
	int result = 0;

	if (rpcb_get_local(net))
		return result;

	mutex_lock(&rpcb_create_local_mutex);
	if (rpcb_get_local(net))
		goto out;

	if (rpcb_create_local_unix(net) != 0)
		result = rpcb_create_local_net(net);

out:
	mutex_unlock(&rpcb_create_local_mutex);
	return result;
}