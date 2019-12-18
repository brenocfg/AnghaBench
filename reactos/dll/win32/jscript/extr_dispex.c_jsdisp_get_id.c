#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ dispex_prop_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PROPF_CONFIGURABLE ; 
 int PROPF_ENUMERABLE ; 
 int PROPF_WRITABLE ; 
 scalar_t__ PROP_DELETED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ensure_prop_name (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,TYPE_1__**) ; 
 int fdexNameEnsure ; 
 int /*<<< orphan*/  find_prop_name_prot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__**) ; 
 int /*<<< orphan*/  prop_to_id (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  string_hash (int /*<<< orphan*/  const*) ; 

HRESULT jsdisp_get_id(jsdisp_t *jsdisp, const WCHAR *name, DWORD flags, DISPID *id)
{
    dispex_prop_t *prop;
    HRESULT hres;

    if(flags & fdexNameEnsure)
        hres = ensure_prop_name(jsdisp, name, PROPF_ENUMERABLE | PROPF_CONFIGURABLE | PROPF_WRITABLE,
                                &prop);
    else
        hres = find_prop_name_prot(jsdisp, string_hash(name), name, &prop);
    if(FAILED(hres))
        return hres;

    if(prop && prop->type!=PROP_DELETED) {
        *id = prop_to_id(jsdisp, prop);
        return S_OK;
    }

    TRACE("not found %s\n", debugstr_w(name));
    return DISP_E_UNKNOWNNAME;
}