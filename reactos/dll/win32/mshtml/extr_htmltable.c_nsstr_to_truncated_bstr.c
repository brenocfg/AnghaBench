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
typedef  int /*<<< orphan*/  nsAString ;
typedef  char PRUnichar ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ SysAllocString (char const*) ; 
 scalar_t__ SysAllocStringLen (char const*,int) ; 
 scalar_t__ isdigitW (char const) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/  const*,char const**) ; 

__attribute__((used)) static HRESULT nsstr_to_truncated_bstr(const nsAString *nsstr, BSTR *ret_ptr)
{
    const PRUnichar *str, *ptr, *end = NULL;
    BSTR ret;

    nsAString_GetData(nsstr, &str);

    for(ptr = str; isdigitW(*ptr); ptr++);
    if(*ptr == '.') {
        for(end = ptr++; isdigitW(*ptr); ptr++);
        if(*ptr)
            end = NULL;
    }

    ret = end ? SysAllocStringLen(str, end-str) : SysAllocString(str);

    *ret_ptr = ret;
    return ret ? S_OK : E_OUTOFMEMORY;
}