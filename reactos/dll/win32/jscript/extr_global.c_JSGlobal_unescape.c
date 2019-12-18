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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int hex_to_int (char const) ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (size_t,char**) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_undefined () ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const**) ; 

__attribute__((used)) static HRESULT JSGlobal_unescape(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
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
        if(*ptr == '%') {
            if(hex_to_int(*(ptr+1))!=-1 && hex_to_int(*(ptr+2))!=-1)
                ptr += 2;
            else if(*(ptr+1)=='u' && hex_to_int(*(ptr+2))!=-1 && hex_to_int(*(ptr+3))!=-1
                    && hex_to_int(*(ptr+4))!=-1 && hex_to_int(*(ptr+5))!=-1)
                ptr += 5;
        }

        len++;
    }

    ret_str = jsstr_alloc_buf(len, &ret);
    if(!ret_str) {
        jsstr_release(str);
        return E_OUTOFMEMORY;
    }

    len = 0;
    for(ptr = buf; *ptr; ptr++) {
        if(*ptr == '%') {
            if(hex_to_int(*(ptr+1))!=-1 && hex_to_int(*(ptr+2))!=-1) {
                ret[len] = (hex_to_int(*(ptr+1))<<4) + hex_to_int(*(ptr+2));
                ptr += 2;
            }
            else if(*(ptr+1)=='u' && hex_to_int(*(ptr+2))!=-1 && hex_to_int(*(ptr+3))!=-1
                    && hex_to_int(*(ptr+4))!=-1 && hex_to_int(*(ptr+5))!=-1) {
                ret[len] = (hex_to_int(*(ptr+2))<<12) + (hex_to_int(*(ptr+3))<<8)
                    + (hex_to_int(*(ptr+4))<<4) + hex_to_int(*(ptr+5));
                ptr += 5;
            }
            else
                ret[len] = *ptr;
        }
        else
            ret[len] = *ptr;

        len++;
    }

    jsstr_release(str);

    if(r)
        *r = jsval_string(ret_str);
    else
        jsstr_release(ret_str);
    return S_OK;
}