#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* priv; } ;
struct TYPE_5__ {TYPE_2__* out_ep; TYPE_2__* in_ep; TYPE_2__ ep0; } ;
typedef  TYPE_1__ dwc_otg_pcd_t ;
typedef  TYPE_2__ dwc_otg_pcd_ep_t ;

/* Variables and functions */
 int MAX_EPS_CHANNELS ; 

__attribute__((used)) static dwc_otg_pcd_ep_t *get_ep_from_handle(dwc_otg_pcd_t * pcd, void *handle)
{
	int i;
	if (pcd->ep0.priv == handle) {
		return &pcd->ep0;
	}
	for (i = 0; i < MAX_EPS_CHANNELS - 1; i++) {
		if (pcd->in_ep[i].priv == handle)
			return &pcd->in_ep[i];
		if (pcd->out_ep[i].priv == handle)
			return &pcd->out_ep[i];
	}

	return NULL;
}