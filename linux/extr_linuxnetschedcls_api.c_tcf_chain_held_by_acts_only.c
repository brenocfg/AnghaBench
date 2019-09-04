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
struct tcf_chain {scalar_t__ refcnt; scalar_t__ action_refcnt; } ;

/* Variables and functions */

__attribute__((used)) static bool tcf_chain_held_by_acts_only(struct tcf_chain *chain)
{
	/* In case all the references are action references, this
	 * chain should not be shown to the user.
	 */
	return chain->refcnt == chain->action_refcnt;
}