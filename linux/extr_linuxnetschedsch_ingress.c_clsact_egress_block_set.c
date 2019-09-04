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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  block_index; } ;
struct clsact_sched_data {TYPE_1__ egress_block_info; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct clsact_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void clsact_egress_block_set(struct Qdisc *sch, u32 block_index)
{
	struct clsact_sched_data *q = qdisc_priv(sch);

	q->egress_block_info.block_index = block_index;
}