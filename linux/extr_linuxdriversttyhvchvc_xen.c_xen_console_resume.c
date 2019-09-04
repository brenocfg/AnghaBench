#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xencons_info {scalar_t__ irq; int /*<<< orphan*/  evtchn; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVC_COOKIE ; 
 int /*<<< orphan*/  rebind_evtchn_irq (int /*<<< orphan*/ ,scalar_t__) ; 
 struct xencons_info* vtermno_to_xencons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_console_update_evtchn (struct xencons_info*) ; 
 int /*<<< orphan*/  xen_initial_domain () ; 

void xen_console_resume(void)
{
	struct xencons_info *info = vtermno_to_xencons(HVC_COOKIE);
	if (info != NULL && info->irq) {
		if (!xen_initial_domain())
			xen_console_update_evtchn(info);
		rebind_evtchn_irq(info->evtchn, info->irq);
	}
}