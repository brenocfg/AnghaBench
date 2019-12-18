#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int prop_cnt; struct TYPE_14__* func_disps; int /*<<< orphan*/  val; TYPE_4__* func_obj; struct TYPE_14__* props; struct TYPE_14__* name; int /*<<< orphan*/  var; } ;
typedef  TYPE_5__ func_obj_entry_t ;
typedef  TYPE_5__ dynamic_prop_t ;
struct TYPE_15__ {TYPE_5__* dynamic_data; TYPE_2__* data; } ;
struct TYPE_12__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
struct TYPE_13__ {TYPE_3__ dispex; int /*<<< orphan*/ * obj; } ;
struct TYPE_11__ {TYPE_1__* data; } ;
struct TYPE_10__ {int func_disp_cnt; } ;
typedef  TYPE_7__ DispatchEx ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (TYPE_5__*) ; 

void release_dispex(DispatchEx *This)
{
    dynamic_prop_t *prop;

    if(!This->dynamic_data)
        return;

    for(prop = This->dynamic_data->props; prop < This->dynamic_data->props + This->dynamic_data->prop_cnt; prop++) {
        VariantClear(&prop->var);
        heap_free(prop->name);
    }

    heap_free(This->dynamic_data->props);

    if(This->dynamic_data->func_disps) {
        func_obj_entry_t *iter;

        for(iter = This->dynamic_data->func_disps; iter < This->dynamic_data->func_disps+This->data->data->func_disp_cnt; iter++) {
            if(iter->func_obj) {
                iter->func_obj->obj = NULL;
                IDispatchEx_Release(&iter->func_obj->dispex.IDispatchEx_iface);
            }
            VariantClear(&iter->val);
        }

        heap_free(This->dynamic_data->func_disps);
    }

    heap_free(This->dynamic_data);
}