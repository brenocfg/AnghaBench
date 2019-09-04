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
struct tc_action {int /*<<< orphan*/  goto_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcf_chain_put_by_act (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcf_action_goto_chain_fini(struct tc_action *a)
{
	tcf_chain_put_by_act(a->goto_chain);
}