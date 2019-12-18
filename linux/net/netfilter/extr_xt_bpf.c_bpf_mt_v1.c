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
struct xt_bpf_info_v1 {int /*<<< orphan*/  filter; } ;
struct xt_action_param {struct xt_bpf_info_v1* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_run_save_cb (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static bool bpf_mt_v1(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_bpf_info_v1 *info = par->matchinfo;

	return !!bpf_prog_run_save_cb(info->filter, (struct sk_buff *) skb);
}