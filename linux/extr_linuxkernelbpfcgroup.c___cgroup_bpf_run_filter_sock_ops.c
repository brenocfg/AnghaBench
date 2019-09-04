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
struct sock {int /*<<< orphan*/  sk_cgrp_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * effective; } ;
struct cgroup {TYPE_1__ bpf; } ;
struct bpf_sock_ops_kern {int dummy; } ;
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_RUN ; 
 int BPF_PROG_RUN_ARRAY (int /*<<< orphan*/ ,struct bpf_sock_ops_kern*,int /*<<< orphan*/ ) ; 
 int EPERM ; 
 struct cgroup* sock_cgroup_ptr (int /*<<< orphan*/ *) ; 

int __cgroup_bpf_run_filter_sock_ops(struct sock *sk,
				     struct bpf_sock_ops_kern *sock_ops,
				     enum bpf_attach_type type)
{
	struct cgroup *cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	int ret;

	ret = BPF_PROG_RUN_ARRAY(cgrp->bpf.effective[type], sock_ops,
				 BPF_PROG_RUN);
	return ret == 1 ? 0 : -EPERM;
}