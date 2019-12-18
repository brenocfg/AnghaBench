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
struct auth_ops {int /*<<< orphan*/  owner; } ;
typedef  size_t rpc_authflavor_t ;

/* Variables and functions */
 size_t RPC_AUTH_MAXFLAVOR ; 
 int /*<<< orphan*/ * authtab ; 
 struct auth_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct auth_ops *
svc_get_auth_ops(rpc_authflavor_t flavor)
{
	struct auth_ops		*aops;

	if (flavor >= RPC_AUTH_MAXFLAVOR)
		return NULL;
	rcu_read_lock();
	aops = rcu_dereference(authtab[flavor]);
	if (aops != NULL && !try_module_get(aops->owner))
		aops = NULL;
	rcu_read_unlock();
	return aops;
}