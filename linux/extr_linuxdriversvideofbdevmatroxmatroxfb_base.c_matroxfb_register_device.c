#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* next; } ;
struct matroxfb_driver {void* (* probe ) (struct matrox_fb_info*) ;TYPE_1__ node; } ;
struct matrox_fb_info {int drivers_count; struct matroxfb_driver** drivers; void** drivers_data; int /*<<< orphan*/  next_fb; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;

/* Variables and functions */
 int MATROXFB_MAX_FB_DRIVERS ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct matroxfb_driver* matroxfb_driver_l (TYPE_2__*) ; 
 TYPE_2__ matroxfb_driver_list ; 
 int /*<<< orphan*/  matroxfb_list ; 
 void* stub1 (struct matrox_fb_info*) ; 

__attribute__((used)) static void matroxfb_register_device(struct matrox_fb_info* minfo) {
	struct matroxfb_driver* drv;
	int i = 0;
	list_add(&minfo->next_fb, &matroxfb_list);
	for (drv = matroxfb_driver_l(matroxfb_driver_list.next);
	     drv != matroxfb_driver_l(&matroxfb_driver_list);
	     drv = matroxfb_driver_l(drv->node.next)) {
		if (drv->probe) {
			void *p = drv->probe(minfo);
			if (p) {
				minfo->drivers_data[i] = p;
				minfo->drivers[i++] = drv;
				if (i == MATROXFB_MAX_FB_DRIVERS)
					break;
			}
		}
	}
	minfo->drivers_count = i;
}