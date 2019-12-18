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
struct tcf_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tcf_block_put (struct tcf_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tcf_block_refcnt_put(struct tcf_block *block, bool rtnl_held)
{
	__tcf_block_put(block, NULL, NULL, rtnl_held);
}