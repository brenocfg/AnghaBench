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
struct TYPE_8__ {TYPE_2__* desc; } ;
typedef  TYPE_3__ vbdisp_t ;
typedef  int /*<<< orphan*/  vbdisp_invoke_type_t ;
struct TYPE_7__ {unsigned int prop_cnt; int func_cnt; scalar_t__ typeinfo; TYPE_1__* props; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  is_public; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DISPID ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  ITypeInfo_GetIDsOfNames (scalar_t__,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ get_func_id (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HRESULT vbdisp_get_id(vbdisp_t *This, BSTR name, vbdisp_invoke_type_t invoke_type, BOOL search_private, DISPID *id)
{
    unsigned i;

    if(get_func_id(This, name, invoke_type, search_private, id))
        return S_OK;

    for(i=0; i < This->desc->prop_cnt; i++) {
        if(!search_private && !This->desc->props[i].is_public)
            continue;

        if(!strcmpiW(This->desc->props[i].name, name)) {
            *id = i + This->desc->func_cnt;
            return S_OK;
        }
    }

    if(This->desc->typeinfo) {
        HRESULT hres;

        hres = ITypeInfo_GetIDsOfNames(This->desc->typeinfo, &name, 1, id);
        if(SUCCEEDED(hres))
            return S_OK;
    }

    *id = -1;
    return DISP_E_UNKNOWNNAME;
}