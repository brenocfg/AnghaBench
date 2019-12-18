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
typedef  int /*<<< orphan*/  tuple ;
struct bpf_sock_tuple {int dummy; } ;
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_CURRENT_NETNS ; 
 int /*<<< orphan*/  bpf_sk_lookup_tcp (struct __sk_buff*,struct bpf_sock_tuple*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lookup_no_release(struct __sk_buff *skb)
{
	struct bpf_sock_tuple tuple = {};
	bpf_sk_lookup_tcp(skb, &tuple, sizeof(tuple), BPF_F_CURRENT_NETNS, 0);
}