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
struct rpc_authops {int (* list_pseudoflavors ) (size_t*,int /*<<< orphan*/ ) ;size_t au_flavor; } ;
typedef  size_t rpc_authflavor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (size_t*) ; 
 int ENOMEM ; 
 size_t RPC_AUTH_MAXFLAVOR ; 
 int /*<<< orphan*/ * auth_flavors ; 
 struct rpc_authops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (size_t*,int /*<<< orphan*/ ) ; 

int
rpcauth_list_flavors(rpc_authflavor_t *array, int size)
{
	const struct rpc_authops *ops;
	rpc_authflavor_t flavor, pseudos[4];
	int i, len, result = 0;

	rcu_read_lock();
	for (flavor = 0; flavor < RPC_AUTH_MAXFLAVOR; flavor++) {
		ops = rcu_dereference(auth_flavors[flavor]);
		if (result >= size) {
			result = -ENOMEM;
			break;
		}

		if (ops == NULL)
			continue;
		if (ops->list_pseudoflavors == NULL) {
			array[result++] = ops->au_flavor;
			continue;
		}
		len = ops->list_pseudoflavors(pseudos, ARRAY_SIZE(pseudos));
		if (len < 0) {
			result = len;
			break;
		}
		for (i = 0; i < len; i++) {
			if (result >= size) {
				result = -ENOMEM;
				break;
			}
			array[result++] = pseudos[i];
		}
	}
	rcu_read_unlock();
	return result;
}