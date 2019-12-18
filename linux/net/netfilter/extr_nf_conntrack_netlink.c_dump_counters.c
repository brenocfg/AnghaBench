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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct nf_conn_counter {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct nf_conn_acct {struct nf_conn_counter* counter; } ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
typedef  enum ctattr_type { ____Placeholder_ctattr_type } ctattr_type ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_COUNTERS_BYTES ; 
 int CTA_COUNTERS_ORIG ; 
 int /*<<< orphan*/  CTA_COUNTERS_PACKETS ; 
 int /*<<< orphan*/  CTA_COUNTERS_PAD ; 
 int CTA_COUNTERS_REPLY ; 
 int IPCTNL_MSG_CT_GET_CTRZERO ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_counters(struct sk_buff *skb, struct nf_conn_acct *acct,
	      enum ip_conntrack_dir dir, int type)
{
	enum ctattr_type attr = dir ? CTA_COUNTERS_REPLY: CTA_COUNTERS_ORIG;
	struct nf_conn_counter *counter = acct->counter;
	struct nlattr *nest_count;
	u64 pkts, bytes;

	if (type == IPCTNL_MSG_CT_GET_CTRZERO) {
		pkts = atomic64_xchg(&counter[dir].packets, 0);
		bytes = atomic64_xchg(&counter[dir].bytes, 0);
	} else {
		pkts = atomic64_read(&counter[dir].packets);
		bytes = atomic64_read(&counter[dir].bytes);
	}

	nest_count = nla_nest_start(skb, attr);
	if (!nest_count)
		goto nla_put_failure;

	if (nla_put_be64(skb, CTA_COUNTERS_PACKETS, cpu_to_be64(pkts),
			 CTA_COUNTERS_PAD) ||
	    nla_put_be64(skb, CTA_COUNTERS_BYTES, cpu_to_be64(bytes),
			 CTA_COUNTERS_PAD))
		goto nla_put_failure;

	nla_nest_end(skb, nest_count);

	return 0;

nla_put_failure:
	return -1;
}