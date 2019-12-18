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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ PROP_DELETED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  find_prop_name_prot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__**) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  prop_get (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_hash (int /*<<< orphan*/  const*) ; 

HRESULT jsdisp_propget_name(jsdisp_t *obj, const WCHAR *name, jsval_t *val)
{
    dispex_prop_t *prop;
    HRESULT hres;

    hres = find_prop_name_prot(obj, string_hash(name), name, &prop);
    if(FAILED(hres))
        return hres;

    if(!prop || prop->type==PROP_DELETED) {
        *val = jsval_undefined();
        return S_OK;
    }

    return prop_get(obj, prop, val);
}