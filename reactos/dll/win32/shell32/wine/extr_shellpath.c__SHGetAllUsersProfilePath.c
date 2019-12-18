#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  szValueName; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  size_t BYTE ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* CSIDL_Data ; 
 scalar_t__ CSIDL_Type_AllUsers ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int SHGFP_TYPE_DEFAULT ; 
 int /*<<< orphan*/  TRACE (char*,int,size_t,...) ; 
 int /*<<< orphan*/  _SHGetDefaultValue (size_t,size_t,...) ; 
 int /*<<< orphan*/  _SHGetUserShellFolderPath (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT _SHGetAllUsersProfilePath(DWORD dwFlags, BYTE folder,
 LPWSTR pszPath)
{
    HRESULT hr;

    TRACE("0x%08x,0x%02x,%p\n", dwFlags, folder, pszPath);

    if (folder >= ARRAY_SIZE(CSIDL_Data))
        return E_INVALIDARG;
    if (CSIDL_Data[folder].type != CSIDL_Type_AllUsers)
        return E_INVALIDARG;
    if (!pszPath)
        return E_INVALIDARG;

    if (dwFlags & SHGFP_TYPE_DEFAULT)
#ifndef __REACTOS__
        hr = _SHGetDefaultValue(folder, pszPath);
#else
        hr = _SHGetDefaultValue(NULL, folder, pszPath);
#endif
    else
    {
#ifndef __REACTOS__
        hr = _SHGetUserShellFolderPath(HKEY_LOCAL_MACHINE, NULL,
#else
        hr = _SHGetUserShellFolderPath(HKEY_LOCAL_MACHINE, NULL, NULL,
#endif
         CSIDL_Data[folder].szValueName, pszPath);
        if (FAILED(hr))
#ifndef __REACTOS__
            hr = _SHGetDefaultValue(folder, pszPath);
#else
            hr = _SHGetDefaultValue(NULL, folder, pszPath);
#endif
    }
    TRACE("returning 0x%08x (output path is %s)\n", hr, debugstr_w(pszPath));
    return hr;
}