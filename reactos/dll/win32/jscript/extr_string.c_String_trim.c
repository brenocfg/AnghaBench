#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  disp; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ iswspace (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * jsstr_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_alloc_len (int /*<<< orphan*/  const*,int) ; 
 unsigned int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT String_trim(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc,
        jsval_t *argv, jsval_t *r)
{
    const WCHAR *str, *begin, *end;
    jsstr_t *jsstr;
    unsigned len;
    HRESULT hres;

    hres = to_flat_string(ctx, jsval_disp(jsthis->u.disp), &jsstr, &str);
    if(FAILED(hres)) {
        WARN("to_flat_string failed: %08x\n", hres);
        return hres;
    }
    len = jsstr_length(jsstr);
    TRACE("%s\n", debugstr_wn(str, len));

    for(begin = str, end = str + len; begin < end && iswspace(*begin); begin++);
    while(end > begin + 1 && iswspace(*(end-1))) end--;

    if(r) {
        jsstr_t *ret;

        if(begin == str && end == str + len)
            ret = jsstr_addref(jsstr);
        else
            ret = jsstr_alloc_len(begin, end - begin);
        if(ret)
            *r = jsval_string(ret);
        else
            hres = E_OUTOFMEMORY;
    }
    jsstr_release(jsstr);
    return hres;
}