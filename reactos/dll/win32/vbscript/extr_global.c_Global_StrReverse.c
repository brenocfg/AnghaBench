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
typedef  void* WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  void** BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int SysStringLen (void**) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_bstr (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,void***) ; 

__attribute__((used)) static HRESULT Global_StrReverse(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    WCHAR *ptr1, *ptr2, ch;
    BSTR ret;
    HRESULT hres;

    TRACE("%s\n", debugstr_variant(arg));

    hres = to_string(arg, &ret);
    if(FAILED(hres))
        return hres;

    ptr1 = ret;
    ptr2 = ret + SysStringLen(ret)-1;
    while(ptr1 < ptr2) {
        ch = *ptr1;
        *ptr1++ = *ptr2;
        *ptr2-- = ch;
    }

    return return_bstr(res, ret);
}