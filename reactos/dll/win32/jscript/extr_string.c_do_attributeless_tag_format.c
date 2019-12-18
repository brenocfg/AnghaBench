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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  get_string_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (scalar_t__,char**) ; 
 int /*<<< orphan*/  jsstr_flush (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 unsigned int lstrlenW (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 

__attribute__((used)) static HRESULT do_attributeless_tag_format(script_ctx_t *ctx, vdisp_t *jsthis, jsval_t *r, const WCHAR *tagname)
{
    unsigned tagname_len;
    jsstr_t *str, *ret;
    WCHAR *ptr;
    HRESULT hres;

    hres = get_string_val(ctx, jsthis, &str);
    if(FAILED(hres))
        return hres;

    if(!r) {
        jsstr_release(str);
        return S_OK;
    }

    tagname_len = lstrlenW(tagname);

    ret = jsstr_alloc_buf(jsstr_length(str) + 2*tagname_len + 5, &ptr);
    if(!ret) {
        jsstr_release(str);
        return E_OUTOFMEMORY;
    }

    *ptr++ = '<';
    memcpy(ptr, tagname, tagname_len*sizeof(WCHAR));
    ptr += tagname_len;
    *ptr++ = '>';

    ptr += jsstr_flush(str, ptr);
    jsstr_release(str);

    *ptr++ = '<';
    *ptr++ = '/';
    memcpy(ptr, tagname, tagname_len*sizeof(WCHAR));
    ptr += tagname_len;
    *ptr = '>';

    *r = jsval_string(ret);
    return S_OK;
}