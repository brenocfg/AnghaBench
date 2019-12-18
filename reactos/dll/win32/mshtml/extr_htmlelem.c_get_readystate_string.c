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
typedef  unsigned char WCHAR ;
typedef  size_t READYSTATE ;
typedef  unsigned char const* LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 size_t READYSTATE_COMPLETE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (unsigned char const* const) ; 
 int /*<<< orphan*/  assert (int) ; 

HRESULT get_readystate_string(READYSTATE readystate, BSTR *p)
{
    static const WCHAR uninitializedW[] = {'u','n','i','n','i','t','i','a','l','i','z','e','d',0};
    static const WCHAR loadingW[] = {'l','o','a','d','i','n','g',0};
    static const WCHAR loadedW[] = {'l','o','a','d','e','d',0};
    static const WCHAR interactiveW[] = {'i','n','t','e','r','a','c','t','i','v','e',0};
    static const WCHAR completeW[] = {'c','o','m','p','l','e','t','e',0};

    static const LPCWSTR readystate_strs[] = {
        uninitializedW,
        loadingW,
        loadedW,
        interactiveW,
        completeW
    };

    assert(readystate <= READYSTATE_COMPLETE);
    *p = SysAllocString(readystate_strs[readystate]);
    return *p ? S_OK : E_OUTOFMEMORY;
}