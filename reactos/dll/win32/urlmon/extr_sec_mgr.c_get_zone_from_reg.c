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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 

__attribute__((used)) static HRESULT get_zone_from_reg(LPCWSTR schema, DWORD *zone)
{
    DWORD res, size;
    HKEY hkey;

    static const WCHAR wszZoneMapProtocolKey[] =
        {'S','o','f','t','w','a','r','e','\\',
         'M','i','c','r','o','s','o','f','t','\\',
         'W','i','n','d','o','w','s','\\',
         'C','u','r','r','e','n','t','V','e','r','s','i','o','n','\\',
         'I','n','t','e','r','n','e','t',' ','S','e','t','t','i','n','g','s','\\',
         'Z','o','n','e','M','a','p','\\',
         'P','r','o','t','o','c','o','l','D','e','f','a','u','l','t','s',0};

    res = RegOpenKeyW(HKEY_CURRENT_USER, wszZoneMapProtocolKey, &hkey);
    if(res != ERROR_SUCCESS) {
        ERR("Could not open key %s\n", debugstr_w(wszZoneMapProtocolKey));
        return E_UNEXPECTED;
    }

    size = sizeof(DWORD);
    res = RegQueryValueExW(hkey, schema, NULL, NULL, (PBYTE)zone, &size);
    RegCloseKey(hkey);
    if(res == ERROR_SUCCESS)
        return S_OK;

    res = RegOpenKeyW(HKEY_LOCAL_MACHINE, wszZoneMapProtocolKey, &hkey);
    if(res != ERROR_SUCCESS) {
        ERR("Could not open key %s\n", debugstr_w(wszZoneMapProtocolKey));
        return E_UNEXPECTED;
    }

    size = sizeof(DWORD);
    res = RegQueryValueExW(hkey, schema, NULL, NULL, (PBYTE)zone, &size);
    RegCloseKey(hkey);
    if(res == ERROR_SUCCESS)
        return S_OK;

    *zone = 3;
    return S_OK;
}