#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; TYPE_3__* list; scalar_t__ pos; TYPE_2__ IEnumVARIANT_iface; } ;
struct TYPE_8__ {int /*<<< orphan*/  IDispatch_iface; } ;
struct TYPE_10__ {TYPE_1__ autoobj; } ;
typedef  TYPE_3__ ListObject ;
typedef  TYPE_4__ ListEnumerator ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ListEnumerator_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,void**) ; 
 TYPE_4__* msi_alloc (int) ; 

__attribute__((used)) static HRESULT create_list_enumerator(ListObject *list, void **ppObj)
{
    ListEnumerator *object;

    TRACE("(%p, %p)\n", list, ppObj);

    object = msi_alloc(sizeof(ListEnumerator));

    /* Set all the VTable references */
    object->IEnumVARIANT_iface.lpVtbl = &ListEnumerator_Vtbl;
    object->ref = 1;

    /* Store data that was passed */
    object->pos = 0;
    object->list = list;
    if (list) IDispatch_AddRef(&list->autoobj.IDispatch_iface);

    *ppObj = object;
    return S_OK;
}