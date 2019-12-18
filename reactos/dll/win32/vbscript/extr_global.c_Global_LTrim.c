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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__* BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__* SysAllocString (scalar_t__*) ; 
 int /*<<< orphan*/  SysFreeString (scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ VT_BSTR ; 
 scalar_t__* V_BSTR (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 scalar_t__ isspaceW (scalar_t__) ; 
 int /*<<< orphan*/  return_bstr (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,scalar_t__**) ; 

__attribute__((used)) static HRESULT Global_LTrim(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    BSTR str, conv_str = NULL;
    WCHAR *ptr;
    HRESULT hres;

    TRACE("%s\n", debugstr_variant(arg));

    if(V_VT(arg) == VT_BSTR) {
        str = V_BSTR(arg);
    }else {
        hres = to_string(arg, &conv_str);
        if(FAILED(hres))
            return hres;
        str = conv_str;
    }

    for(ptr = str; *ptr && isspaceW(*ptr); ptr++);

    str = SysAllocString(ptr);
    SysFreeString(conv_str);
    if(!str)
        return E_OUTOFMEMORY;

    return return_bstr(res, str);
}