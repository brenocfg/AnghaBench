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
typedef  scalar_t__ uint64_t ;
struct xencons_info {scalar_t__ evtchn; } ;
struct TYPE_4__ {scalar_t__ evtchn; } ;
struct TYPE_5__ {TYPE_1__ domU; } ;
struct TYPE_6__ {TYPE_2__ console; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVM_PARAM_CONSOLE_EVTCHN ; 
 int hvm_get_parameter (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ xen_hvm_domain () ; 
 TYPE_3__* xen_start_info ; 

__attribute__((used)) static void xen_console_update_evtchn(struct xencons_info *info)
{
	if (xen_hvm_domain()) {
		uint64_t v = 0;
		int err;

		err = hvm_get_parameter(HVM_PARAM_CONSOLE_EVTCHN, &v);
		if (!err && v)
			info->evtchn = v;
	} else
		info->evtchn = xen_start_info->console.domU.evtchn;
}