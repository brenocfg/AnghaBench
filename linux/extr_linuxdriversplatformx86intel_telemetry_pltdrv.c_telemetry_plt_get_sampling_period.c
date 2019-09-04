#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  max_period; int /*<<< orphan*/  min_period; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_period; int /*<<< orphan*/  min_period; } ;
struct TYPE_6__ {TYPE_2__ ioss_config; TYPE_1__ pss_config; } ;

/* Variables and functions */
 TYPE_3__* telm_conf ; 

__attribute__((used)) static int telemetry_plt_get_sampling_period(u8 *pss_min_period,
					     u8 *pss_max_period,
					     u8 *ioss_min_period,
					     u8 *ioss_max_period)
{
	*pss_min_period = telm_conf->pss_config.min_period;
	*pss_max_period = telm_conf->pss_config.max_period;
	*ioss_min_period = telm_conf->ioss_config.min_period;
	*ioss_max_period = telm_conf->ioss_config.max_period;

	return 0;
}