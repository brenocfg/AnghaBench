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
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int int_to_char (int const) ; 
 scalar_t__ is_ecma_nonblank (int const) ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (scalar_t__,int**) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_undefined () ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int const**) ; 

__attribute__((used)) static HRESULT JSGlobal_escape(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsstr_t *ret_str, *str;
    const WCHAR *ptr, *buf;
    DWORD len = 0;
    WCHAR *ret;
    HRESULT hres;

    TRACE("\n");

    if(!argc) {
        if(r)
            *r = jsval_string(jsstr_undefined());
        return S_OK;
    }

    hres = to_flat_string(ctx, argv[0], &str, &buf);
    if(FAILED(hres))
        return hres;

    for(ptr = buf; *ptr; ptr++) {
        if(*ptr > 0xff)
            len += 6;
        else if(is_ecma_nonblank(*ptr))
            len++;
        else
            len += 3;
    }

    ret_str = jsstr_alloc_buf(len, &ret);
    if(!ret_str) {
        jsstr_release(str);
        return E_OUTOFMEMORY;
    }

    len = 0;
    for(ptr = buf; *ptr; ptr++) {
        if(*ptr > 0xff) {
            ret[len++] = '%';
            ret[len++] = 'u';
            ret[len++] = int_to_char(*ptr >> 12);
            ret[len++] = int_to_char((*ptr >> 8) & 0xf);
            ret[len++] = int_to_char((*ptr >> 4) & 0xf);
            ret[len++] = int_to_char(*ptr & 0xf);
        }
        else if(is_ecma_nonblank(*ptr))
            ret[len++] = *ptr;
        else {
            ret[len++] = '%';
            ret[len++] = int_to_char(*ptr >> 4);
            ret[len++] = int_to_char(*ptr & 0xf);
        }
    }

    jsstr_release(str);

    if(r)
        *r = jsval_string(ret_str);
    else
        jsstr_release(ret_str);
    return S_OK;
}