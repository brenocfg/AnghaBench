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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct nf_conntrack_l4proto {int /*<<< orphan*/  me; } ;

/* Variables and functions */
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_l4proto nf_conntrack_l4proto_generic ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

const struct nf_conntrack_l4proto *
nf_ct_l4proto_find_get(u_int16_t l3num, u_int8_t l4num)
{
	const struct nf_conntrack_l4proto *p;

	rcu_read_lock();
	p = __nf_ct_l4proto_find(l3num, l4num);
	if (!try_module_get(p->me))
		p = &nf_conntrack_l4proto_generic;
	rcu_read_unlock();

	return p;
}