#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ dispex_prop_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ PROP_DELETED ; 
 int /*<<< orphan*/  find_prop_name_prot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__**) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  prop_get (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_hash (char*) ; 
 int /*<<< orphan*/  swprintf (char*,char const*,char*) ; 

HRESULT jsdisp_get_idx(jsdisp_t *obj, DWORD idx, jsval_t *r)
{
    WCHAR name[12];
    dispex_prop_t *prop;
    HRESULT hres;

    static const WCHAR formatW[] = {'%','d',0};

    swprintf(name, formatW, idx);

    hres = find_prop_name_prot(obj, string_hash(name), name, &prop);
    if(FAILED(hres))
        return hres;

    if(!prop || prop->type==PROP_DELETED) {
        *r = jsval_undefined();
        return DISP_E_UNKNOWNNAME;
    }

    return prop_get(obj, prop, r);
}