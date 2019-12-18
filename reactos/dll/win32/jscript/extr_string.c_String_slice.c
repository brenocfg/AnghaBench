#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  get_string_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ is_int32 (double) ; 
 int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_substr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static HRESULT String_slice(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    int start=0, end, length;
    jsstr_t *str;
    double d;
    HRESULT hres;

    TRACE("\n");

    hres = get_string_val(ctx, jsthis, &str);
    if(FAILED(hres))
        return hres;

    length = jsstr_length(str);
    if(argc) {
        hres = to_integer(ctx, argv[0], &d);
        if(FAILED(hres)) {
            jsstr_release(str);
            return hres;
        }

        if(is_int32(d)) {
            start = d;
            if(start < 0) {
                start = length + start;
                if(start < 0)
                    start = 0;
            }else if(start > length) {
                start = length;
            }
        }else if(d > 0) {
            start = length;
        }
    }

    if(argc >= 2) {
        hres = to_integer(ctx, argv[1], &d);
        if(FAILED(hres)) {
            jsstr_release(str);
            return hres;
        }

        if(is_int32(d)) {
            end = d;
            if(end < 0) {
                end = length + end;
                if(end < 0)
                    end = 0;
            }else if(end > length) {
                end = length;
            }
        }else {
            end = d < 0.0 ? 0 : length;
        }
    }else {
        end = length;
    }

    if(end < start)
        end = start;

    if(r) {
        jsstr_t *retstr = jsstr_substr(str, start, end-start);
        if(!retstr) {
            jsstr_release(str);
            return E_OUTOFMEMORY;
        }

        *r = jsval_string(retstr);
    }

    jsstr_release(str);
    return S_OK;
}