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
struct vc_data {int dummy; } ;
struct TYPE_3__ {int topscan; } ;
struct TYPE_4__ {TYPE_1__ cset; } ;

/* Variables and functions */
 int logo_active ; 
 scalar_t__ newport_show_logo () ; 
 TYPE_2__* npregs ; 
 scalar_t__ topscan ; 

__attribute__((used)) static int newport_switch(struct vc_data *vc)
{
	static int logo_drawn = 0;

	topscan = 0;
	npregs->cset.topscan = 0x3ff;

	if (!logo_drawn) {
		if (newport_show_logo()) {
			logo_drawn = 1;
			logo_active = 1;
		}
	}

	return 1;
}