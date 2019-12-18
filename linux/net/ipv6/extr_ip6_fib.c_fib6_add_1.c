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
typedef  int /*<<< orphan*/  u8 ;
struct in6_addr {int dummy; } ;
struct rt6key {struct in6_addr addr; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {scalar_t__ fib6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; } ;
struct fib6_node {int fn_bit; int fn_flags; int /*<<< orphan*/  left; int /*<<< orphan*/  right; int /*<<< orphan*/  parent; int /*<<< orphan*/  leaf; } ;
struct fib6_info {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct fib6_node* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct fib6_node*) ; 
 int /*<<< orphan*/  RT6_TRACE (char*) ; 
 int RTN_RTINFO ; 
 int RTN_TL_ROOT ; 
 int __ipv6_addr_diff (struct in6_addr*,struct in6_addr*,int) ; 
 scalar_t__ addr_bit_set (struct in6_addr*,int) ; 
 int /*<<< orphan*/  fib6_info_hold (void*) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 int /*<<< orphan*/  ipv6_prefix_equal (struct in6_addr*,struct in6_addr*,int) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct fib6_node* node_alloc (struct net*) ; 
 int /*<<< orphan*/  node_free_immediate (struct net*,struct fib6_node*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct fib6_node*) ; 
 void* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fib6_node *fib6_add_1(struct net *net,
				    struct fib6_table *table,
				    struct fib6_node *root,
				    struct in6_addr *addr, int plen,
				    int offset, int allow_create,
				    int replace_required,
				    struct netlink_ext_ack *extack)
{
	struct fib6_node *fn, *in, *ln;
	struct fib6_node *pn = NULL;
	struct rt6key *key;
	int	bit;
	__be32	dir = 0;

	RT6_TRACE("fib6_add_1\n");

	/* insert node in tree */

	fn = root;

	do {
		struct fib6_info *leaf = rcu_dereference_protected(fn->leaf,
					    lockdep_is_held(&table->tb6_lock));
		key = (struct rt6key *)((u8 *)leaf + offset);

		/*
		 *	Prefix match
		 */
		if (plen < fn->fn_bit ||
		    !ipv6_prefix_equal(&key->addr, addr, fn->fn_bit)) {
			if (!allow_create) {
				if (replace_required) {
					NL_SET_ERR_MSG(extack,
						       "Can not replace route - no match found");
					pr_warn("Can't replace route, no match found\n");
					return ERR_PTR(-ENOENT);
				}
				pr_warn("NLM_F_CREATE should be set when creating new route\n");
			}
			goto insert_above;
		}

		/*
		 *	Exact match ?
		 */

		if (plen == fn->fn_bit) {
			/* clean up an intermediate node */
			if (!(fn->fn_flags & RTN_RTINFO)) {
				RCU_INIT_POINTER(fn->leaf, NULL);
				fib6_info_release(leaf);
			/* remove null_entry in the root node */
			} else if (fn->fn_flags & RTN_TL_ROOT &&
				   rcu_access_pointer(fn->leaf) ==
				   net->ipv6.fib6_null_entry) {
				RCU_INIT_POINTER(fn->leaf, NULL);
			}

			return fn;
		}

		/*
		 *	We have more bits to go
		 */

		/* Try to walk down on tree. */
		dir = addr_bit_set(addr, fn->fn_bit);
		pn = fn;
		fn = dir ?
		     rcu_dereference_protected(fn->right,
					lockdep_is_held(&table->tb6_lock)) :
		     rcu_dereference_protected(fn->left,
					lockdep_is_held(&table->tb6_lock));
	} while (fn);

	if (!allow_create) {
		/* We should not create new node because
		 * NLM_F_REPLACE was specified without NLM_F_CREATE
		 * I assume it is safe to require NLM_F_CREATE when
		 * REPLACE flag is used! Later we may want to remove the
		 * check for replace_required, because according
		 * to netlink specification, NLM_F_CREATE
		 * MUST be specified if new route is created.
		 * That would keep IPv6 consistent with IPv4
		 */
		if (replace_required) {
			NL_SET_ERR_MSG(extack,
				       "Can not replace route - no match found");
			pr_warn("Can't replace route, no match found\n");
			return ERR_PTR(-ENOENT);
		}
		pr_warn("NLM_F_CREATE should be set when creating new route\n");
	}
	/*
	 *	We walked to the bottom of tree.
	 *	Create new leaf node without children.
	 */

	ln = node_alloc(net);

	if (!ln)
		return ERR_PTR(-ENOMEM);
	ln->fn_bit = plen;
	RCU_INIT_POINTER(ln->parent, pn);

	if (dir)
		rcu_assign_pointer(pn->right, ln);
	else
		rcu_assign_pointer(pn->left, ln);

	return ln;


insert_above:
	/*
	 * split since we don't have a common prefix anymore or
	 * we have a less significant route.
	 * we've to insert an intermediate node on the list
	 * this new node will point to the one we need to create
	 * and the current
	 */

	pn = rcu_dereference_protected(fn->parent,
				       lockdep_is_held(&table->tb6_lock));

	/* find 1st bit in difference between the 2 addrs.

	   See comment in __ipv6_addr_diff: bit may be an invalid value,
	   but if it is >= plen, the value is ignored in any case.
	 */

	bit = __ipv6_addr_diff(addr, &key->addr, sizeof(*addr));

	/*
	 *		(intermediate)[in]
	 *	          /	   \
	 *	(new leaf node)[ln] (old node)[fn]
	 */
	if (plen > bit) {
		in = node_alloc(net);
		ln = node_alloc(net);

		if (!in || !ln) {
			if (in)
				node_free_immediate(net, in);
			if (ln)
				node_free_immediate(net, ln);
			return ERR_PTR(-ENOMEM);
		}

		/*
		 * new intermediate node.
		 * RTN_RTINFO will
		 * be off since that an address that chooses one of
		 * the branches would not match less specific routes
		 * in the other branch
		 */

		in->fn_bit = bit;

		RCU_INIT_POINTER(in->parent, pn);
		in->leaf = fn->leaf;
		fib6_info_hold(rcu_dereference_protected(in->leaf,
				lockdep_is_held(&table->tb6_lock)));

		/* update parent pointer */
		if (dir)
			rcu_assign_pointer(pn->right, in);
		else
			rcu_assign_pointer(pn->left, in);

		ln->fn_bit = plen;

		RCU_INIT_POINTER(ln->parent, in);
		rcu_assign_pointer(fn->parent, in);

		if (addr_bit_set(addr, bit)) {
			rcu_assign_pointer(in->right, ln);
			rcu_assign_pointer(in->left, fn);
		} else {
			rcu_assign_pointer(in->left, ln);
			rcu_assign_pointer(in->right, fn);
		}
	} else { /* plen <= bit */

		/*
		 *		(new leaf node)[ln]
		 *	          /	   \
		 *	     (old node)[fn] NULL
		 */

		ln = node_alloc(net);

		if (!ln)
			return ERR_PTR(-ENOMEM);

		ln->fn_bit = plen;

		RCU_INIT_POINTER(ln->parent, pn);

		if (addr_bit_set(&key->addr, plen))
			RCU_INIT_POINTER(ln->right, fn);
		else
			RCU_INIT_POINTER(ln->left, fn);

		rcu_assign_pointer(fn->parent, ln);

		if (dir)
			rcu_assign_pointer(pn->right, ln);
		else
			rcu_assign_pointer(pn->left, ln);
	}
	return ln;
}