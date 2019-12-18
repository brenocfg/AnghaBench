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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  scalar_t__ PRUnichar ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SysAllocString (scalar_t__ const*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__ const*) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,scalar_t__ const**) ; 

HRESULT return_nsstr(nsresult nsres, nsAString *nsstr, BSTR *p)
{
    const PRUnichar *str;

    if(NS_FAILED(nsres)) {
        ERR("failed: %08x\n", nsres);
        nsAString_Finish(nsstr);
        return E_FAIL;
    }

    nsAString_GetData(nsstr, &str);
    TRACE("ret %s\n", debugstr_w(str));
    if(*str) {
        *p = SysAllocString(str);
        if(!*p)
            return E_OUTOFMEMORY;
    }else {
        *p = NULL;
    }

    nsAString_Finish(nsstr);
    return S_OK;
}