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
typedef  int /*<<< orphan*/  func_info_t ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; int /*<<< orphan*/ * info; int /*<<< orphan*/ * obj; TYPE_2__ IUnknown_iface; int /*<<< orphan*/  dispex; } ;
typedef  TYPE_1__ func_disp_t ;
typedef  int /*<<< orphan*/  DispatchEx ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionUnkVtbl ; 
 int /*<<< orphan*/  function_dispex ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static func_disp_t *create_func_disp(DispatchEx *obj, func_info_t *info)
{
    func_disp_t *ret;

    ret = heap_alloc_zero(sizeof(func_disp_t));
    if(!ret)
        return NULL;

    ret->IUnknown_iface.lpVtbl = &FunctionUnkVtbl;
    init_dispex(&ret->dispex, &ret->IUnknown_iface,  &function_dispex);
    ret->ref = 1;
    ret->obj = obj;
    ret->info = info;

    return ret;
}