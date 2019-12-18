#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ NumberInstance ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_FRACTION_DIGITS_OUT_OF_RANGE ; 
 int /*<<< orphan*/  JS_E_NUMBER_EXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  is_finite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 TYPE_1__* number_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * number_to_fixed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  throw_range_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT Number_toFixed(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    NumberInstance *number;
    DOUBLE val;
    INT prec = 0;
    jsstr_t *str;
    HRESULT hres;

    TRACE("\n");

    if(!(number = number_this(jsthis)))
        return throw_type_error(ctx, JS_E_NUMBER_EXPECTED, NULL);

    if(argc) {
        hres = to_int32(ctx, argv[0], &prec);
        if(FAILED(hres))
            return hres;

        if(prec<0 || prec>20)
            return throw_range_error(ctx, JS_E_FRACTION_DIGITS_OUT_OF_RANGE, NULL);
    }

    val = number->value;
    if(!is_finite(val)) {
        hres = to_string(ctx, jsval_number(val), &str);
        if(FAILED(hres))
            return hres;
    }else {
        str = number_to_fixed(val, prec);
        if(!str)
            return E_OUTOFMEMORY;
    }

    if(r)
        *r = jsval_string(str);
    else
        jsstr_release(str);
    return S_OK;
}