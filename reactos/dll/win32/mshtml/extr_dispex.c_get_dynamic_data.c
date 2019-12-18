#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dispex_dynamic_data_t ;
struct TYPE_8__ {int /*<<< orphan*/ * dynamic_data; TYPE_1__* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* populate_props ) (TYPE_3__*) ;} ;
struct TYPE_6__ {TYPE_2__* vtbl; } ;
typedef  TYPE_3__ DispatchEx ;

/* Variables and functions */
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static inline dispex_dynamic_data_t *get_dynamic_data(DispatchEx *This)
{
    if(This->dynamic_data)
        return This->dynamic_data;

    This->dynamic_data = heap_alloc_zero(sizeof(dispex_dynamic_data_t));
    if(!This->dynamic_data)
        return NULL;

    if(This->data->vtbl && This->data->vtbl->populate_props)
        This->data->vtbl->populate_props(This);

    return This->dynamic_data;
}