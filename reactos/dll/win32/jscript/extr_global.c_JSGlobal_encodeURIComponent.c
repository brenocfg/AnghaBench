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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_INVALID_URI_CHAR ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* int_to_char (char) ; 
 scalar_t__ is_uri_unescaped (scalar_t__ const) ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (int,scalar_t__**) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_undefined () ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_uri_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__ const**) ; 

__attribute__((used)) static HRESULT JSGlobal_encodeURIComponent(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsstr_t *str, *ret_str;
    char buf[4];
    const WCHAR *ptr, *uri;
    DWORD len = 0, size, i;
    WCHAR *ret;
    HRESULT hres;

    TRACE("\n");

    if(!argc) {
        if(r)
            *r = jsval_string(jsstr_undefined());
        return S_OK;
    }

    hres = to_flat_string(ctx, argv[0], &str, &uri);
    if(FAILED(hres))
        return hres;

    for(ptr = uri; *ptr; ptr++) {
        if(is_uri_unescaped(*ptr))
            len++;
        else {
            size = WideCharToMultiByte(CP_UTF8, 0, ptr, 1, NULL, 0, NULL, NULL);
            if(!size) {
                jsstr_release(str);
                return throw_uri_error(ctx, JS_E_INVALID_URI_CHAR, NULL);
            }
            len += size*3;
        }
    }

    ret_str = jsstr_alloc_buf(len, &ret);
    if(!ret_str) {
        jsstr_release(str);
        return E_OUTOFMEMORY;
    }

    for(ptr = uri; *ptr; ptr++) {
        if(is_uri_unescaped(*ptr)) {
            *ret++ = *ptr;
        }else {
            size = WideCharToMultiByte(CP_UTF8, 0, ptr, 1, buf, sizeof(buf), NULL, NULL);
            for(i=0; i<size; i++) {
                *ret++ = '%';
                *ret++ = int_to_char((BYTE)buf[i] >> 4);
                *ret++ = int_to_char(buf[i] & 0x0f);
            }
        }
    }

    jsstr_release(str);

    if(r)
        *r = jsval_string(ret_str);
    else
        jsstr_release(ret_str);
    return S_OK;
}