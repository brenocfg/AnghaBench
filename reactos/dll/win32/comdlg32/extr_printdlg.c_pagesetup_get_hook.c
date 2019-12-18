#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dlgw; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  TYPE_3__ pagesetup_data ;
typedef  int hook_type ;
struct TYPE_5__ {int /*<<< orphan*/ * lpfnPagePaintHook; int /*<<< orphan*/ * lpfnPageSetupHook; } ;
typedef  int /*<<< orphan*/ * LPPAGESETUPHOOK ;

/* Variables and functions */
#define  page_paint_hook 129 
#define  page_setup_hook 128 

__attribute__((used)) static inline LPPAGESETUPHOOK pagesetup_get_hook(const pagesetup_data *data, hook_type which)
{
    switch(which)
    {
    case page_setup_hook: return data->u.dlgw->lpfnPageSetupHook;
    case page_paint_hook: return data->u.dlgw->lpfnPagePaintHook;
    }
    return NULL;
}