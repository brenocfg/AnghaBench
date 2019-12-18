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
struct set_elem {int /*<<< orphan*/  rcu; int /*<<< orphan*/  id; int /*<<< orphan*/  list; } ;
struct list_set {int /*<<< orphan*/  net; } ;
struct ip_set {struct list_set* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __list_set_del_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_put_byindex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_replace_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
list_set_replace(struct ip_set *set, struct set_elem *e, struct set_elem *old)
{
	struct list_set *map = set->data;

	list_replace_rcu(&old->list, &e->list);
	ip_set_put_byindex(map->net, old->id);
	call_rcu(&old->rcu, __list_set_del_rcu);
}