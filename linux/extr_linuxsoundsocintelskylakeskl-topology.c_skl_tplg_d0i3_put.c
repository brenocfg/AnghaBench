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
struct skl_d0i3_data {int /*<<< orphan*/  non_streaming; int /*<<< orphan*/  streaming; int /*<<< orphan*/  non_d0i3; } ;
struct skl {TYPE_1__* skl_sst; } ;
typedef  enum d0i3_capability { ____Placeholder_d0i3_capability } d0i3_capability ;
struct TYPE_2__ {struct skl_d0i3_data d0i3; } ;

/* Variables and functions */
#define  SKL_D0I3_NONE 130 
#define  SKL_D0I3_NON_STREAMING 129 
#define  SKL_D0I3_STREAMING 128 

void skl_tplg_d0i3_put(struct skl *skl, enum d0i3_capability caps)
{
	struct skl_d0i3_data *d0i3 =  &skl->skl_sst->d0i3;

	switch (caps) {
	case SKL_D0I3_NONE:
		d0i3->non_d0i3--;
		break;

	case SKL_D0I3_STREAMING:
		d0i3->streaming--;
		break;

	case SKL_D0I3_NON_STREAMING:
		d0i3->non_streaming--;
		break;
	}
}