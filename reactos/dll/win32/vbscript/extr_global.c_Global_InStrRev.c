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
typedef  int /*<<< orphan*/  vbdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  const* BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  MAKE_VBSERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/  const*) ; 
 int SysStringLen (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  VBSE_ILLEGAL_NULL_USE ; 
 scalar_t__ VT_NULL ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  to_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT Global_InStrRev(vbdisp_t *This, VARIANT *args, unsigned args_cnt, VARIANT *res)
{
    int start, ret = 0;
    BSTR str1, str2;
    HRESULT hres;

    TRACE("%s %s arg_cnt=%u\n", debugstr_variant(args), debugstr_variant(args+1), args_cnt);

    if(args_cnt > 3) {
        FIXME("Unsupported args\n");
        return E_NOTIMPL;
    }

    assert(2 <= args_cnt && args_cnt <= 4);

    if(V_VT(args) == VT_NULL || V_VT(args+1) == VT_NULL || (args_cnt > 2 && V_VT(args+2) == VT_NULL))
        return MAKE_VBSERROR(VBSE_ILLEGAL_NULL_USE);

    hres = to_string(args, &str1);
    if(FAILED(hres))
        return hres;

    hres = to_string(args+1, &str2);
    if(SUCCEEDED(hres)) {
        if(args_cnt > 2) {
            hres = to_int(args+2, &start);
            if(SUCCEEDED(hres) && start <= 0) {
                FIXME("Unsupported start %d\n", start);
                hres = E_NOTIMPL;
            }
        }else {
            start = SysStringLen(str1);
        }
    } else {
        str2 = NULL;
    }

    if(SUCCEEDED(hres)) {
        const WCHAR *ptr;
        size_t len;

        len = SysStringLen(str2);
        if(start >= len && start <= SysStringLen(str1)) {
            for(ptr = str1+start-SysStringLen(str2); ptr >= str1; ptr--) {
                if(!memcmp(ptr, str2, len*sizeof(WCHAR))) {
                    ret = ptr-str1+1;
                    break;
                }
            }
        }
    }

    SysFreeString(str1);
    SysFreeString(str2);
    if(FAILED(hres))
        return hres;

    return return_int(res, ret);
}