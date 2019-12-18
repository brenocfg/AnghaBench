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
typedef  size_t eventid_t ;
struct TYPE_6__ {TYPE_1__** event_table; } ;
typedef  TYPE_2__ event_target_t ;
typedef  int /*<<< orphan*/  VARIANT_BOOL ;
struct TYPE_5__ {size_t handler_cnt; int /*<<< orphan*/ ** handlers; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  EventTarget ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 size_t EVENTID_LAST ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  alloc_handler_vector (TYPE_2__*,size_t,size_t) ; 
 size_t attr_to_eid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_event (int /*<<< orphan*/ *,size_t) ; 
 TYPE_2__* get_event_target_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT attach_event(EventTarget *event_target, BSTR name, IDispatch *disp, VARIANT_BOOL *res)
{
    event_target_t *data;
    eventid_t eid;
    DWORD i = 0;

    eid = attr_to_eid(name);
    if(eid == EVENTID_LAST) {
        WARN("Unknown event\n");
        *res = VARIANT_TRUE;
        return S_OK;
    }

    data = get_event_target_data(event_target, TRUE);
    if(!data)
        return E_OUTOFMEMORY;

    if(data->event_table[eid]) {
        while(i < data->event_table[eid]->handler_cnt && data->event_table[eid]->handlers[i])
            i++;
        if(i == data->event_table[eid]->handler_cnt && !alloc_handler_vector(data, eid, i+1))
            return E_OUTOFMEMORY;
    }else if(!alloc_handler_vector(data, eid, i+1)) {
        return E_OUTOFMEMORY;
    }

    IDispatch_AddRef(disp);
    data->event_table[eid]->handlers[i] = disp;

    bind_event(event_target, eid);

    *res = VARIANT_TRUE;
    return S_OK;
}