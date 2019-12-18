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
struct smc_pnettable {int /*<<< orphan*/  lock; int /*<<< orphan*/  pnetlist; } ;
struct smc_net {struct smc_pnettable pnettable; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct smc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_net_id ; 

int smc_pnet_net_init(struct net *net)
{
	struct smc_net *sn = net_generic(net, smc_net_id);
	struct smc_pnettable *pnettable = &sn->pnettable;

	INIT_LIST_HEAD(&pnettable->pnetlist);
	rwlock_init(&pnettable->lock);

	return 0;
}