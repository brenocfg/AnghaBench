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
struct TYPE_4__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ variant_val_t ;
typedef  int /*<<< orphan*/  exec_ctx_t ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int E_NOTIMPL ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int S_OK ; 
#define  VT_BOOL 131 
#define  VT_I2 130 
#define  VT_I4 129 
#define  VT_NULL 128 
 int /*<<< orphan*/  V_BOOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_I2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/ ) ; 
 int V_VT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_val (TYPE_1__*) ; 
 int stack_pop_val (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int stack_pop_bool(exec_ctx_t *ctx, BOOL *b)
{
    variant_val_t val;
    HRESULT hres;

    hres = stack_pop_val(ctx, &val);
    if(FAILED(hres))
        return hres;

    switch (V_VT(val.v))
    {
    case VT_BOOL:
        *b = V_BOOL(val.v);
        break;
    case VT_NULL:
        *b = FALSE;
        break;
    case VT_I2:
        *b = V_I2(val.v);
        break;
    case VT_I4:
        *b = V_I4(val.v);
        break;
    default:
        FIXME("unsupported for %s\n", debugstr_variant(val.v));
        release_val(&val);
        return E_NOTIMPL;
    }
    return S_OK;
}