#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * jsdisp; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_10__ {int /*<<< orphan*/  length; int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_3__ ArrayInstance ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_JSCRIPT_EXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* array_this (TYPE_2__*) ; 
 int /*<<< orphan*/  is_jsdisp (TYPE_2__*) ; 
 int /*<<< orphan*/  jsdisp_propget_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lengthW ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT get_length(script_ctx_t *ctx, vdisp_t *vdisp, jsdisp_t **jsthis, DWORD *ret)
{
    ArrayInstance *array;
    jsval_t val;
    HRESULT hres;

    array = array_this(vdisp);
    if(array) {
        *jsthis = &array->dispex;
        *ret = array->length;
        return S_OK;
    }

    if(!is_jsdisp(vdisp))
        return throw_type_error(ctx, JS_E_JSCRIPT_EXPECTED, NULL);

    hres = jsdisp_propget_name(vdisp->u.jsdisp, lengthW, &val);
    if(FAILED(hres))
        return hres;

    hres = to_uint32(ctx, val, ret);
    jsval_release(val);
    if(FAILED(hres))
        return hres;

    *jsthis = vdisp->u.jsdisp;
    return S_OK;
}