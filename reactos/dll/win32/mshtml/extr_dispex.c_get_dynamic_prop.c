#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  var; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ dynamic_prop_t ;
struct TYPE_9__ {int prop_cnt; int buf_size; TYPE_1__* props; } ;
typedef  TYPE_2__ dispex_dynamic_data_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DispatchEx ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int DYNPROP_DELETED ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int fdexNameCaseInsensitive ; 
 int fdexNameEnsure ; 
 TYPE_2__* get_dynamic_data (int /*<<< orphan*/ *) ; 
 TYPE_1__* heap_alloc (int) ; 
 TYPE_1__* heap_realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT get_dynamic_prop(DispatchEx *This, const WCHAR *name, DWORD flags, dynamic_prop_t **ret)
{
    const BOOL alloc = flags & fdexNameEnsure;
    dispex_dynamic_data_t *data;
    dynamic_prop_t *prop;

    data = get_dynamic_data(This);
    if(!data)
        return E_OUTOFMEMORY;

    for(prop = data->props; prop < data->props+data->prop_cnt; prop++) {
        if(flags & fdexNameCaseInsensitive ? !strcmpiW(prop->name, name) : !strcmpW(prop->name, name)) {
            if(prop->flags & DYNPROP_DELETED) {
                if(!alloc)
                    return DISP_E_UNKNOWNNAME;
                prop->flags &= ~DYNPROP_DELETED;
            }
            *ret = prop;
            return S_OK;
        }
    }

    if(!alloc)
        return DISP_E_UNKNOWNNAME;

    TRACE("creating dynamic prop %s\n", debugstr_w(name));

    if(!data->buf_size) {
        data->props = heap_alloc(sizeof(dynamic_prop_t)*4);
        if(!data->props)
            return E_OUTOFMEMORY;
        data->buf_size = 4;
    }else if(data->buf_size == data->prop_cnt) {
        dynamic_prop_t *new_props;

        new_props = heap_realloc(data->props, sizeof(dynamic_prop_t)*(data->buf_size<<1));
        if(!new_props)
            return E_OUTOFMEMORY;

        data->props = new_props;
        data->buf_size <<= 1;
    }

    prop = data->props + data->prop_cnt;

    prop->name = heap_strdupW(name);
    if(!prop->name)
        return E_OUTOFMEMORY;

    VariantInit(&prop->var);
    prop->flags = 0;
    data->prop_cnt++;
    *ret = prop;
    return S_OK;
}