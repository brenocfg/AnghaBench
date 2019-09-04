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
struct telemetry_evtlog {int dummy; } ;
typedef  enum telemetry_unit { ____Placeholder_telemetry_unit } telemetry_unit ;
struct TYPE_4__ {TYPE_1__* telem_ops; } ;
struct TYPE_3__ {int (* raw_read_eventlog ) (int,struct telemetry_evtlog*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int,struct telemetry_evtlog*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ telm_core_conf ; 

int telemetry_raw_read_events(enum telemetry_unit telem_unit,
			      struct telemetry_evtlog *evtlog, int len)
{
	return telm_core_conf.telem_ops->raw_read_eventlog(telem_unit, evtlog,
							   len, 0);
}