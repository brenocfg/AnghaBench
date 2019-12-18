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
struct rds_sock {int /*<<< orphan*/  rs_bound_addr; int /*<<< orphan*/  rs_bound_node; int /*<<< orphan*/  rs_bound_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  bind_hash_table ; 
 int /*<<< orphan*/  ht_parms ; 
 int /*<<< orphan*/  in6addr_any ; 
 scalar_t__ ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_sock_put (struct rds_sock*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rds_remove_bound(struct rds_sock *rs)
{

	if (ipv6_addr_any(&rs->rs_bound_addr))
		return;

	rdsdebug("rs %p unbinding from %pI6c:%d\n",
		 rs, &rs->rs_bound_addr,
		 ntohs(rs->rs_bound_port));

	rhashtable_remove_fast(&bind_hash_table, &rs->rs_bound_node, ht_parms);
	rds_sock_put(rs);
	rs->rs_bound_addr = in6addr_any;
}