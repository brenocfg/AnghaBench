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
struct intel_bts {TYPE_1__ queues; } ;

/* Variables and functions */
 int intel_bts_setup_queues (struct intel_bts*) ; 

__attribute__((used)) static inline int intel_bts_update_queues(struct intel_bts *bts)
{
	if (bts->queues.new_data) {
		bts->queues.new_data = false;
		return intel_bts_setup_queues(bts);
	}
	return 0;
}