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
struct xencons_info {int /*<<< orphan*/ * intf; } ;
struct TYPE_4__ {int /*<<< orphan*/  evtchn; } ;
struct TYPE_5__ {TYPE_1__ domU; } ;
struct TYPE_6__ {TYPE_2__ console; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HVC_COOKIE ; 
 struct xencons_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct xencons_info* vtermno_to_xencons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_pv_domain () ; 
 TYPE_3__* xen_start_info ; 
 int /*<<< orphan*/  xencons_info_pv_init (struct xencons_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xencons_lock ; 

__attribute__((used)) static int xen_pv_console_init(void)
{
	struct xencons_info *info;

	if (!xen_pv_domain())
		return -ENODEV;

	if (!xen_start_info->console.domU.evtchn)
		return -ENODEV;

	info = vtermno_to_xencons(HVC_COOKIE);
	if (!info) {
		info = kzalloc(sizeof(struct xencons_info), GFP_KERNEL);
		if (!info)
			return -ENOMEM;
	} else if (info->intf != NULL) {
		/* already configured */
		return 0;
	}
	spin_lock(&xencons_lock);
	xencons_info_pv_init(info, HVC_COOKIE);
	spin_unlock(&xencons_lock);

	return 0;
}