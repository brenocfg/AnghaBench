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
struct telemetry_unit_config {int ssram_evts_used; TYPE_2__* telem_evts; } ;
typedef  enum telemetry_unit { ____Placeholder_telemetry_unit } telemetry_unit ;
struct TYPE_6__ {TYPE_1__* plt_config; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {struct telemetry_unit_config ioss_config; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_3__ telm_core_conf ; 

__attribute__((used)) static inline int telemetry_get_iossevtname(enum telemetry_unit telem_unit,
					    const char **name, int len)
{
	struct telemetry_unit_config iosscfg;
	int i;

	if (!(telm_core_conf.plt_config))
		return -EINVAL;

	iosscfg = telm_core_conf.plt_config->ioss_config;

	if (len > iosscfg.ssram_evts_used)
		len = iosscfg.ssram_evts_used;

	for (i = 0; i < len; i++)
		name[i] = iosscfg.telem_evts[i].name;

	return 0;

}