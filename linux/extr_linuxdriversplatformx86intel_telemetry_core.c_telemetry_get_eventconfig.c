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
struct telemetry_evtconfig {int dummy; } ;
struct TYPE_4__ {TYPE_1__* telem_ops; } ;
struct TYPE_3__ {int (* get_eventconfig ) (struct telemetry_evtconfig*,struct telemetry_evtconfig*,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct telemetry_evtconfig*,struct telemetry_evtconfig*,int,int) ; 
 TYPE_2__ telm_core_conf ; 

int telemetry_get_eventconfig(struct telemetry_evtconfig *pss_evtconfig,
			      struct telemetry_evtconfig *ioss_evtconfig,
			      int pss_len, int ioss_len)
{
	return telm_core_conf.telem_ops->get_eventconfig(pss_evtconfig,
							 ioss_evtconfig,
							 pss_len, ioss_len);
}