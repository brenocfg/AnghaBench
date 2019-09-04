#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {TYPE_1__* telem_ops; } ;
struct TYPE_3__ {int (* get_sampling_period ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ telm_core_conf ; 

int telemetry_get_sampling_period(u8 *pss_min_period, u8 *pss_max_period,
				  u8 *ioss_min_period, u8 *ioss_max_period)
{
	return telm_core_conf.telem_ops->get_sampling_period(pss_min_period,
							     pss_max_period,
							     ioss_min_period,
							     ioss_max_period);
}