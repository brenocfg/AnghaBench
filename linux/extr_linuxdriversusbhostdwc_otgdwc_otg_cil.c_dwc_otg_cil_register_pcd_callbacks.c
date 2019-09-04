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
struct TYPE_5__ {TYPE_2__* pcd_cb; } ;
typedef  TYPE_1__ dwc_otg_core_if_t ;
struct TYPE_6__ {void* p; } ;
typedef  TYPE_2__ dwc_otg_cil_callbacks_t ;

/* Variables and functions */

void dwc_otg_cil_register_pcd_callbacks(dwc_otg_core_if_t * core_if,
					dwc_otg_cil_callbacks_t * cb, void *p)
{
	core_if->pcd_cb = cb;
	cb->p = p;
}