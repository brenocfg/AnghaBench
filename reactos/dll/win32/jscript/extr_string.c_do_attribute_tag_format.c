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
 int /*<<< orphan*/  get_string_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (scalar_t__,char**) ; 
 int /*<<< orphan*/  jsstr_flush (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_undefined () ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 unsigned int lstrlenW (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT do_attribute_tag_format(script_ctx_t *ctx, vdisp_t *jsthis, unsigned argc, jsval_t *argv, jsval_t *r,
        const WCHAR *tagname, const WCHAR *attrname)
{
    jsstr_t *str, *attr_value = NULL;
    HRESULT hres;

    hres = get_string_val(ctx, jsthis, &str);
    if(FAILED(hres))
        return hres;

    if(argc) {
        hres = to_string(ctx, argv[0], &attr_value);
        if(FAILED(hres)) {
            jsstr_release(str);
            return hres;
        }
    }else {
        attr_value = jsstr_undefined();
    }

    if(r) {
        unsigned attrname_len = lstrlenW(attrname);
        unsigned tagname_len = lstrlenW(tagname);
        jsstr_t *ret;
        WCHAR *ptr;

        ret = jsstr_alloc_buf(2*tagname_len + attrname_len + jsstr_length(attr_value) + jsstr_length(str) + 9, &ptr);
        if(ret) {
            *ptr++ = '<';
            memcpy(ptr, tagname, tagname_len*sizeof(WCHAR));
            ptr += tagname_len;
            *ptr++ = ' ';
            memcpy(ptr, attrname, attrname_len*sizeof(WCHAR));
            ptr += attrname_len;
            *ptr++ = '=';
            *ptr++ = '"';
            ptr += jsstr_flush(attr_value, ptr);
            *ptr++ = '"';
            *ptr++ = '>';
            ptr += jsstr_flush(str, ptr);

            *ptr++ = '<';
            *ptr++ = '/';
            memcpy(ptr, tagname, tagname_len*sizeof(WCHAR));
            ptr += tagname_len;
            *ptr = '>';

            *r = jsval_string(ret);
        }else {
            hres = E_OUTOFMEMORY;
        }
    }

    jsstr_release(attr_value);
    jsstr_release(str);
    return hres;
}