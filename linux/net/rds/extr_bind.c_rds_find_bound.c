#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rds_sock {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_3__ {int /*<<< orphan*/  sk_refcnt; } ;

/* Variables and functions */
 int RDS_BOUND_KEY_LEN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  __rds_create_bind_key (int /*<<< orphan*/ *,struct in6_addr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_hash_table ; 
 int /*<<< orphan*/  ht_parms ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_1__* rds_rs_to_sk (struct rds_sock*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_sock*,struct in6_addr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct rds_sock* rhashtable_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_flag (TYPE_1__*,int /*<<< orphan*/ ) ; 

struct rds_sock *rds_find_bound(const struct in6_addr *addr, __be16 port,
				__u32 scope_id)
{
	u8 key[RDS_BOUND_KEY_LEN];
	struct rds_sock *rs;

	__rds_create_bind_key(key, addr, port, scope_id);
	rcu_read_lock();
	rs = rhashtable_lookup(&bind_hash_table, key, ht_parms);
	if (rs && (sock_flag(rds_rs_to_sk(rs), SOCK_DEAD) ||
		   !refcount_inc_not_zero(&rds_rs_to_sk(rs)->sk_refcnt)))
		rs = NULL;

	rcu_read_unlock();

	rdsdebug("returning rs %p for %pI6c:%u\n", rs, addr,
		 ntohs(port));

	return rs;
}