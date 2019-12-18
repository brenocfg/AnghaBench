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
struct sock {scalar_t__ sk_family; int /*<<< orphan*/  sk_cgrp_data; } ;
struct sk_buff {unsigned int data; struct sock* sk; } ;
struct TYPE_2__ {int /*<<< orphan*/ * effective; } ;
struct cgroup {TYPE_1__ bpf; } ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int BPF_CGROUP_INET_EGRESS ; 
 int BPF_PROG_CGROUP_INET_EGRESS_RUN_ARRAY (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int BPF_PROG_RUN_ARRAY (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int EPERM ; 
 int /*<<< orphan*/  __bpf_prog_run_save_cb ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  bpf_compute_and_save_data_end (struct sk_buff*,void**) ; 
 int /*<<< orphan*/  bpf_restore_data_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  sk_fullsock (struct sock*) ; 
 unsigned int skb_network_header (struct sk_buff*) ; 
 struct cgroup* sock_cgroup_ptr (int /*<<< orphan*/ *) ; 

int __cgroup_bpf_run_filter_skb(struct sock *sk,
				struct sk_buff *skb,
				enum bpf_attach_type type)
{
	unsigned int offset = skb->data - skb_network_header(skb);
	struct sock *save_sk;
	void *saved_data_end;
	struct cgroup *cgrp;
	int ret;

	if (!sk || !sk_fullsock(sk))
		return 0;

	if (sk->sk_family != AF_INET && sk->sk_family != AF_INET6)
		return 0;

	cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	save_sk = skb->sk;
	skb->sk = sk;
	__skb_push(skb, offset);

	/* compute pointers for the bpf prog */
	bpf_compute_and_save_data_end(skb, &saved_data_end);

	if (type == BPF_CGROUP_INET_EGRESS) {
		ret = BPF_PROG_CGROUP_INET_EGRESS_RUN_ARRAY(
			cgrp->bpf.effective[type], skb, __bpf_prog_run_save_cb);
	} else {
		ret = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[type], skb,
					  __bpf_prog_run_save_cb);
		ret = (ret == 1 ? 0 : -EPERM);
	}
	bpf_restore_data_end(skb, saved_data_end);
	__skb_pull(skb, offset);
	skb->sk = save_sk;

	return ret;
}