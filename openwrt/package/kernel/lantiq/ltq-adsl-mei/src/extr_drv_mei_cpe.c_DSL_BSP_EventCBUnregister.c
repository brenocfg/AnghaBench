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
struct TYPE_5__ {int /*<<< orphan*/ * pData; int /*<<< orphan*/ * function; } ;
struct TYPE_4__ {size_t event; } ;
typedef  TYPE_1__ DSL_BSP_EventCallBack_t ;

/* Variables and functions */
 size_t DSL_BSP_CB_FIRST ; 
 size_t DSL_BSP_CB_LAST ; 
 int EINVAL ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*,...) ; 
 TYPE_2__* dsl_bsp_event_callback ; 

int DSL_BSP_EventCBUnregister(DSL_BSP_EventCallBack_t *p)
{
	if (!p) {
                IFX_MEI_EMSG("Invalid parameter!\n");
                return -EINVAL;
	}
        if (p->event > DSL_BSP_CB_LAST || p->event < DSL_BSP_CB_FIRST) {
                IFX_MEI_EMSG("Invalid Event %d\n", p->event);
                return -EINVAL;
        }
        if (dsl_bsp_event_callback[p->event].function) {
                IFX_MEI_EMSG("Unregistering Event %d...\n", p->event);
                dsl_bsp_event_callback[p->event].function = NULL;
                dsl_bsp_event_callback[p->event].pData    = NULL;
        } else {
                IFX_MEI_EMSG("Event %d is not registered!\n", p->event);
                return -1;
        }
        return 0;
}