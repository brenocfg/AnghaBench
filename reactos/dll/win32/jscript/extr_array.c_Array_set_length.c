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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ DOUBLE ;
typedef  TYPE_1__ ArrayInstance ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_INVALID_LENGTH ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,scalar_t__) ; 
 TYPE_1__* array_from_jsdisp (int /*<<< orphan*/ *) ; 
 scalar_t__ floor (scalar_t__) ; 
 int /*<<< orphan*/  jsdisp_delete_idx (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  throw_range_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static HRESULT Array_set_length(script_ctx_t *ctx, jsdisp_t *jsthis, jsval_t value)
{
    ArrayInstance *This = array_from_jsdisp(jsthis);
    DOUBLE len = -1;
    DWORD i;
    HRESULT hres;

    TRACE("%p %d\n", This, This->length);

    hres = to_number(ctx, value, &len);
    if(FAILED(hres))
        return hres;

    len = floor(len);
    if(len!=(DWORD)len)
        return throw_range_error(ctx, JS_E_INVALID_LENGTH, NULL);

    for(i=len; i < This->length; i++) {
        hres = jsdisp_delete_idx(&This->dispex, i);
        if(FAILED(hres))
            return hres;
    }

    This->length = len;
    return S_OK;
}