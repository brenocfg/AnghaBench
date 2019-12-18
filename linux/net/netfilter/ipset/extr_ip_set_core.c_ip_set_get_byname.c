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
struct ip_set_net {size_t ip_set_max; int /*<<< orphan*/  ip_set_list; } ;
struct ip_set {int /*<<< orphan*/  name; } ;
typedef  size_t ip_set_id_t ;

/* Variables and functions */
 size_t IPSET_INVALID_ID ; 
 scalar_t__ STRNCMP (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  __ip_set_get (struct ip_set*) ; 
 struct ip_set_net* ip_set_pernet (struct net*) ; 
 struct ip_set** rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

ip_set_id_t
ip_set_get_byname(struct net *net, const char *name, struct ip_set **set)
{
	ip_set_id_t i, index = IPSET_INVALID_ID;
	struct ip_set *s;
	struct ip_set_net *inst = ip_set_pernet(net);

	rcu_read_lock();
	for (i = 0; i < inst->ip_set_max; i++) {
		s = rcu_dereference(inst->ip_set_list)[i];
		if (s && STRNCMP(s->name, name)) {
			__ip_set_get(s);
			index = i;
			*set = s;
			break;
		}
	}
	rcu_read_unlock();

	return index;
}