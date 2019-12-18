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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  RRF_RT_REG_SZ ; 
 scalar_t__ RegGetValueW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_BSTR ; 
 int /*<<< orphan*/  VT_UI4 ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_variant (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT get_stringvalue( HKEY root, const WCHAR *subkey, const WCHAR *name, VARIANT *value, VARIANT *retval )
{
    HRESULT hr = S_OK;
    BSTR str = NULL;
    DWORD size;
    LONG res;

    TRACE("%p, %s, %s\n", root, debugstr_w(subkey), debugstr_w(name));

    if ((res = RegGetValueW( root, subkey, name, RRF_RT_REG_SZ, NULL, NULL, &size ))) goto done;
    if (!(str = SysAllocStringLen( NULL, size / sizeof(WCHAR) - 1 )))
    {
        hr = E_OUTOFMEMORY;
        goto done;
    }
    if (!(res = RegGetValueW( root, subkey, name, RRF_RT_REG_SZ, NULL, str, &size )))
        set_variant( VT_BSTR, 0, str, value );

done:
    set_variant( VT_UI4, res, NULL, retval );
    if (res) SysFreeString( str );
    return hr;
}