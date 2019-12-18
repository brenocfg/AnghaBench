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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct nf_conntrack_helper {int /*<<< orphan*/  me; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 struct nf_conntrack_helper* __nf_conntrack_helper_find (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ request_module (char*,char const*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct nf_conntrack_helper *
nf_conntrack_helper_try_module_get(const char *name, u16 l3num, u8 protonum)
{
	struct nf_conntrack_helper *h;

	rcu_read_lock();

	h = __nf_conntrack_helper_find(name, l3num, protonum);
#ifdef CONFIG_MODULES
	if (h == NULL) {
		rcu_read_unlock();
		if (request_module("nfct-helper-%s", name) == 0) {
			rcu_read_lock();
			h = __nf_conntrack_helper_find(name, l3num, protonum);
		} else {
			return h;
		}
	}
#endif
	if (h != NULL && !try_module_get(h->me))
		h = NULL;
	if (h != NULL && !refcount_inc_not_zero(&h->refcnt)) {
		module_put(h->me);
		h = NULL;
	}

	rcu_read_unlock();

	return h;
}