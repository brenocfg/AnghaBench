#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tipc_subscr {int dummy; } ;
struct TYPE_3__ {struct tipc_subscr s; } ;
struct tipc_subscription {int /*<<< orphan*/  net; TYPE_1__ evt; } ;
struct tipc_service {int /*<<< orphan*/  lock; } ;
struct tipc_net {int /*<<< orphan*/  nametbl_lock; } ;
struct name_table {int /*<<< orphan*/ * services; } ;
struct TYPE_4__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 size_t hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ seq ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct name_table* tipc_name_table (int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (int /*<<< orphan*/ ) ; 
 struct tipc_service* tipc_service_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tipc_service* tipc_service_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_service_subscribe (struct tipc_service*,struct tipc_subscription*) ; 
 int /*<<< orphan*/  tipc_sub_read (struct tipc_subscr*,int /*<<< orphan*/ ) ; 

bool tipc_nametbl_subscribe(struct tipc_subscription *sub)
{
	struct name_table *nt = tipc_name_table(sub->net);
	struct tipc_net *tn = tipc_net(sub->net);
	struct tipc_subscr *s = &sub->evt.s;
	u32 type = tipc_sub_read(s, seq.type);
	struct tipc_service *sc;
	bool res = true;

	spin_lock_bh(&tn->nametbl_lock);
	sc = tipc_service_find(sub->net, type);
	if (!sc)
		sc = tipc_service_create(type, &nt->services[hash(type)]);
	if (sc) {
		spin_lock_bh(&sc->lock);
		tipc_service_subscribe(sc, sub);
		spin_unlock_bh(&sc->lock);
	} else {
		pr_warn("Failed to subscribe for {%u,%u,%u}\n", type,
			tipc_sub_read(s, seq.lower),
			tipc_sub_read(s, seq.upper));
		res = false;
	}
	spin_unlock_bh(&tn->nametbl_lock);
	return res;
}