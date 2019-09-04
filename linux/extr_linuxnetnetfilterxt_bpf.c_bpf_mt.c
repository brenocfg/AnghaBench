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
struct xt_bpf_info {int /*<<< orphan*/  filter; } ;
struct xt_action_param {struct xt_bpf_info* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int BPF_PROG_RUN (int /*<<< orphan*/ ,struct sk_buff const*) ; 

__attribute__((used)) static bool bpf_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_bpf_info *info = par->matchinfo;

	return BPF_PROG_RUN(info->filter, skb);
}