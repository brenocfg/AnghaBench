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
struct bpf_sock_ops_kern {scalar_t__ op; } ;

/* Variables and functions */
 scalar_t__ BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB ; 
 scalar_t__ BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB ; 

__attribute__((used)) static bool bpf_is_valid_sock_op(struct bpf_sock_ops_kern *ops)
{
	return ops->op == BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB ||
	       ops->op == BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB;
}