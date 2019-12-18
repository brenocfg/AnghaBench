#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  jsdisp; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_9__ {int flags; } ;
typedef  TYPE_3__ property_desc_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int PROPF_ENUMERABLE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_jsdisp (TYPE_2__*) ; 
 scalar_t__ jsdisp_get_own_property (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_bool (int) ; 
 scalar_t__ to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT Object_propertyIsEnumerable(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    property_desc_t prop_desc;
    const WCHAR *name;
    jsstr_t *name_str;
    HRESULT hres;

    TRACE("\n");

    if(argc != 1) {
        FIXME("argc %d not supported\n", argc);
        return E_NOTIMPL;
    }

    if(!is_jsdisp(jsthis)) {
        FIXME("Host object this\n");
        return E_FAIL;
    }

    hres = to_flat_string(ctx, argv[0], &name_str, &name);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_get_own_property(jsthis->u.jsdisp, name, TRUE, &prop_desc);
    jsstr_release(name_str);
    if(FAILED(hres) && hres != DISP_E_UNKNOWNNAME)
        return hres;

    if(r)
        *r = jsval_bool(hres == S_OK && (prop_desc.flags & PROPF_ENUMERABLE) != 0);
    return S_OK;
}