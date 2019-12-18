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
typedef  int LONG ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  KEY_ENUMERATE_SUB_KEYS ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegEnumKeyW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_UI4 ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free_bstr_array (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_variant (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ to_bstr_array (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT enum_key( HKEY root, const WCHAR *subkey, VARIANT *names, VARIANT *retval )
{
    HKEY hkey;
    HRESULT hr = S_OK;
    WCHAR buf[256];
    BSTR *strings, *tmp;
    DWORD count = 2, len = ARRAY_SIZE( buf );
    LONG res, i = 0;

    TRACE("%p, %s\n", root, debugstr_w(subkey));

    if (!(strings = heap_alloc( count * sizeof(BSTR) ))) return E_OUTOFMEMORY;
    if ((res = RegOpenKeyExW( root, subkey, 0, KEY_ENUMERATE_SUB_KEYS, &hkey )))
    {
        set_variant( VT_UI4, res, NULL, retval );
        heap_free( strings );
        return S_OK;
    }
    for (;;)
    {
        if (i >= count)
        {
            count *= 2;
            if (!(tmp = heap_realloc( strings, count * sizeof(BSTR) )))
            {
                RegCloseKey( hkey );
                return E_OUTOFMEMORY;
            }
            strings = tmp;
        }
        if ((res = RegEnumKeyW( hkey, i, buf, len )) == ERROR_NO_MORE_ITEMS)
        {
            if (i) res = ERROR_SUCCESS;
            break;
        }
        if (res) break;
        if (!(strings[i] = SysAllocString( buf )))
        {
            for (i--; i >= 0; i--) SysFreeString( strings[i] );
            hr = E_OUTOFMEMORY;
            break;
        }
        i++;
    }
    if (hr == S_OK && !res)
    {
        hr = to_bstr_array( strings, i, names );
        free_bstr_array( strings, i );
    }
    set_variant( VT_UI4, res, NULL, retval );
    RegCloseKey( hkey );
    heap_free( strings );
    return hr;
}