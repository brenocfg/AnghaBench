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
struct ip_set {int /*<<< orphan*/  elements; struct list_set* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __list_set_del_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_put_byindex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
list_set_del(struct ip_set *set, struct set_elem *e)
{
	struct list_set *map = set->data;

	set->elements--;
	list_del_rcu(&e->list);
	ip_set_put_byindex(map->net, e->id);
	call_rcu(&e->rcu, __list_set_del_rcu);
}