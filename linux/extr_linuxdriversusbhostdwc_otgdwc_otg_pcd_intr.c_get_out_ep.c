#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ num; } ;
struct TYPE_12__ {TYPE_2__ dwc_ep; } ;
struct TYPE_11__ {TYPE_4__* out_ep; TYPE_4__ ep0; } ;
typedef  TYPE_3__ dwc_otg_pcd_t ;
typedef  TYPE_4__ dwc_otg_pcd_ep_t ;
struct TYPE_13__ {TYPE_1__* dev_if; } ;
struct TYPE_9__ {int num_out_eps; } ;

/* Variables and functions */
 TYPE_7__* GET_CORE_IF (TYPE_3__*) ; 

__attribute__((used)) static inline dwc_otg_pcd_ep_t *get_out_ep(dwc_otg_pcd_t * pcd, uint32_t ep_num)
{
	int i;
	int num_out_eps = GET_CORE_IF(pcd)->dev_if->num_out_eps;
	if (ep_num == 0) {
		return &pcd->ep0;
	} else {
		for (i = 0; i < num_out_eps; ++i) {
			if (pcd->out_ep[i].dwc_ep.num == ep_num)
				return &pcd->out_ep[i];
		}
		return 0;
	}
}