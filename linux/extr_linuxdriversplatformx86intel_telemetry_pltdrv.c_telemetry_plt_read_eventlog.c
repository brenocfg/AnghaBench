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
struct telemetry_evtlog {int dummy; } ;
typedef  enum telemetry_unit { ____Placeholder_telemetry_unit } telemetry_unit ;
struct TYPE_2__ {int /*<<< orphan*/  telem_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int telemetry_plt_raw_read_eventlog (int,struct telemetry_evtlog*,int,int) ; 
 TYPE_1__* telm_conf ; 

__attribute__((used)) static int telemetry_plt_read_eventlog(enum telemetry_unit telem_unit,
		struct telemetry_evtlog *evtlog, int len, int log_all_evts)
{
	int ret;

	mutex_lock(&(telm_conf->telem_lock));
	ret = telemetry_plt_raw_read_eventlog(telem_unit, evtlog,
					      len, log_all_evts);
	mutex_unlock(&(telm_conf->telem_lock));

	return ret;
}