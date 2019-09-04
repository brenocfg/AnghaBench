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
struct sock_fprog_kern {int /*<<< orphan*/  filter; } ;
struct sock {int /*<<< orphan*/  sk_filter; } ;
struct sk_filter {TYPE_1__* prog; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {struct sock_fprog_kern* orig_prog; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 unsigned int bpf_classic_proglen (struct sock_fprog_kern*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int,unsigned int) ; 
 struct sk_filter* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int sock_diag_put_filterinfo(bool may_report_filterinfo, struct sock *sk,
			     struct sk_buff *skb, int attrtype)
{
	struct sock_fprog_kern *fprog;
	struct sk_filter *filter;
	struct nlattr *attr;
	unsigned int flen;
	int err = 0;

	if (!may_report_filterinfo) {
		nla_reserve(skb, attrtype, 0);
		return 0;
	}

	rcu_read_lock();
	filter = rcu_dereference(sk->sk_filter);
	if (!filter)
		goto out;

	fprog = filter->prog->orig_prog;
	if (!fprog)
		goto out;

	flen = bpf_classic_proglen(fprog);

	attr = nla_reserve(skb, attrtype, flen);
	if (attr == NULL) {
		err = -EMSGSIZE;
		goto out;
	}

	memcpy(nla_data(attr), fprog->filter, flen);
out:
	rcu_read_unlock();
	return err;
}