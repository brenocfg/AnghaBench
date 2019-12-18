#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct caif_net {int /*<<< orphan*/  cfg; TYPE_1__ caifdevs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caif_net_id ; 
 int /*<<< orphan*/  cfcnfg_create () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct caif_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int caif_init_net(struct net *net)
{
	struct caif_net *caifn = net_generic(net, caif_net_id);
	INIT_LIST_HEAD(&caifn->caifdevs.list);
	mutex_init(&caifn->caifdevs.lock);

	caifn->cfg = cfcnfg_create();
	if (!caifn->cfg)
		return -ENOMEM;

	return 0;
}