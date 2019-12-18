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
struct fq_codel_flow {int /*<<< orphan*/ * head; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtnl_kfree_skbs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fq_codel_flow_purge(struct fq_codel_flow *flow)
{
	rtnl_kfree_skbs(flow->head, flow->tail);
	flow->head = NULL;
}