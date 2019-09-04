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
typedef  size_t u8 ;
struct nf_nat_l4proto {size_t l4proto; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IPPROTO_MAX ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct nf_nat_l4proto const*,struct nf_nat_l4proto const*) ; 
 struct nf_nat_l4proto** kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nf_nat_l4proto const nf_nat_l4proto_unknown ; 
 struct nf_nat_l4proto const*** nf_nat_l4protos ; 
 int /*<<< orphan*/  nf_nat_proto_mutex ; 
 struct nf_nat_l4proto const* rcu_dereference_protected (struct nf_nat_l4proto const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

int nf_nat_l4proto_register(u8 l3proto, const struct nf_nat_l4proto *l4proto)
{
	const struct nf_nat_l4proto **l4protos;
	unsigned int i;
	int ret = 0;

	mutex_lock(&nf_nat_proto_mutex);
	if (nf_nat_l4protos[l3proto] == NULL) {
		l4protos = kmalloc_array(IPPROTO_MAX,
					 sizeof(struct nf_nat_l4proto *),
					 GFP_KERNEL);
		if (l4protos == NULL) {
			ret = -ENOMEM;
			goto out;
		}

		for (i = 0; i < IPPROTO_MAX; i++)
			RCU_INIT_POINTER(l4protos[i], &nf_nat_l4proto_unknown);

		/* Before making proto_array visible to lockless readers,
		 * we must make sure its content is committed to memory.
		 */
		smp_wmb();

		nf_nat_l4protos[l3proto] = l4protos;
	}

	if (rcu_dereference_protected(
			nf_nat_l4protos[l3proto][l4proto->l4proto],
			lockdep_is_held(&nf_nat_proto_mutex)
			) != &nf_nat_l4proto_unknown) {
		ret = -EBUSY;
		goto out;
	}
	RCU_INIT_POINTER(nf_nat_l4protos[l3proto][l4proto->l4proto], l4proto);
 out:
	mutex_unlock(&nf_nat_proto_mutex);
	return ret;
}