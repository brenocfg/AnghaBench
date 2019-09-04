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
struct TYPE_2__ {int new_data; } ;
struct intel_pt {TYPE_1__ queues; } ;

/* Variables and functions */
 int intel_pt_setup_queues (struct intel_pt*) ; 

__attribute__((used)) static inline int intel_pt_update_queues(struct intel_pt *pt)
{
	if (pt->queues.new_data) {
		pt->queues.new_data = false;
		return intel_pt_setup_queues(pt);
	}
	return 0;
}