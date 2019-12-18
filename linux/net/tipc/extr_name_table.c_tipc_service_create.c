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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_service {int /*<<< orphan*/  service_list; int /*<<< orphan*/  subscriptions; int /*<<< orphan*/  ranges; int /*<<< orphan*/  type; int /*<<< orphan*/  lock; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,struct hlist_head*) ; 
 struct tipc_service* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tipc_service *tipc_service_create(u32 type, struct hlist_head *hd)
{
	struct tipc_service *service = kzalloc(sizeof(*service), GFP_ATOMIC);

	if (!service) {
		pr_warn("Service creation failed, no memory\n");
		return NULL;
	}

	spin_lock_init(&service->lock);
	service->type = type;
	service->ranges = RB_ROOT;
	INIT_HLIST_NODE(&service->service_list);
	INIT_LIST_HEAD(&service->subscriptions);
	hlist_add_head_rcu(&service->service_list, hd);
	return service;
}