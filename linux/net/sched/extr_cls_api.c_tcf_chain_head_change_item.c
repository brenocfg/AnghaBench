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
struct tcf_proto {int dummy; } ;
struct tcf_filter_chain_list_item {int /*<<< orphan*/  chain_head_change_priv; int /*<<< orphan*/  (* chain_head_change ) (struct tcf_proto*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tcf_proto*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcf_chain_head_change_item(struct tcf_filter_chain_list_item *item,
				       struct tcf_proto *tp_head)
{
	if (item->chain_head_change)
		item->chain_head_change(tp_head, item->chain_head_change_priv);
}