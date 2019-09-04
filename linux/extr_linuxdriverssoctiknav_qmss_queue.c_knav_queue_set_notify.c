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
struct knav_range_info {TYPE_1__* ops; } ;
struct knav_queue_inst {struct knav_range_info* range; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_notify ) (struct knav_range_info*,struct knav_queue_inst*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct knav_range_info*,struct knav_queue_inst*,int) ; 

__attribute__((used)) static void knav_queue_set_notify(struct knav_queue_inst *inst, bool enabled)
{
	struct knav_range_info *range = inst->range;

	if (range->ops && range->ops->set_notify)
		range->ops->set_notify(range, inst, enabled);
}