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
struct flowi4 {int /*<<< orphan*/  flowi4_scope; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi4_mark; } ;
struct fib_table {int /*<<< orphan*/  tb_id; } ;
struct fib_result_nl {int /*<<< orphan*/  scope; int /*<<< orphan*/  type; int /*<<< orphan*/  nh_sel; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  err; int /*<<< orphan*/  tb_id; int /*<<< orphan*/  tb_id_in; int /*<<< orphan*/  fl_scope; int /*<<< orphan*/  fl_tos; int /*<<< orphan*/  fl_addr; int /*<<< orphan*/  fl_mark; } ;
struct fib_result {int /*<<< orphan*/  scope; int /*<<< orphan*/  type; int /*<<< orphan*/  nh_sel; int /*<<< orphan*/  prefixlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  FIB_LOOKUP_NOREF ; 
 struct fib_table* fib_get_table (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_table_lookup (struct fib_table*,struct flowi4*,struct fib_result*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void nl_fib_lookup(struct net *net, struct fib_result_nl *frn)
{

	struct fib_result       res;
	struct flowi4           fl4 = {
		.flowi4_mark = frn->fl_mark,
		.daddr = frn->fl_addr,
		.flowi4_tos = frn->fl_tos,
		.flowi4_scope = frn->fl_scope,
	};
	struct fib_table *tb;

	rcu_read_lock();

	tb = fib_get_table(net, frn->tb_id_in);

	frn->err = -ENOENT;
	if (tb) {
		local_bh_disable();

		frn->tb_id = tb->tb_id;
		frn->err = fib_table_lookup(tb, &fl4, &res, FIB_LOOKUP_NOREF);

		if (!frn->err) {
			frn->prefixlen = res.prefixlen;
			frn->nh_sel = res.nh_sel;
			frn->type = res.type;
			frn->scope = res.scope;
		}
		local_bh_enable();
	}

	rcu_read_unlock();
}