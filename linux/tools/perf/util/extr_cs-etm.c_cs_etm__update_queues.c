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
struct cs_etm_auxtrace {TYPE_1__ queues; } ;

/* Variables and functions */
 int cs_etm__setup_queues (struct cs_etm_auxtrace*) ; 

__attribute__((used)) static int cs_etm__update_queues(struct cs_etm_auxtrace *etm)
{
	if (etm->queues.new_data) {
		etm->queues.new_data = false;
		return cs_etm__setup_queues(etm);
	}

	return 0;
}