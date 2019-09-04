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
struct knav_queue_inst {TYPE_1__* range; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int RANGE_RESERVED ; 

__attribute__((used)) static inline bool knav_queue_is_reserved(struct knav_queue_inst *inst)
{
	return inst->range->flags & RANGE_RESERVED;
}