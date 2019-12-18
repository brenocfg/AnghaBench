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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  size_t LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SafeArrayCreateVector (int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  SafeArrayDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SafeArrayPutElement (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int VT_ARRAY ; 
 int VT_BSTR ; 
 int /*<<< orphan*/  set_variant (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT to_bstr_array( BSTR *strings, DWORD count, VARIANT *var )
{
    SAFEARRAY *sa;
    HRESULT hr;
    LONG i;

    if (!(sa = SafeArrayCreateVector( VT_BSTR, 0, count ))) return E_OUTOFMEMORY;
    for (i = 0; i < count; i++)
    {
        if ((hr = SafeArrayPutElement( sa, &i, strings[i] )) != S_OK)
        {
            SafeArrayDestroy( sa );
            return hr;
        }
    }
    set_variant( VT_BSTR|VT_ARRAY, 0, sa, var );
    return S_OK;
}