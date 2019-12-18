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
typedef  int URLZONEREG ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
#define  URLACTION_ACTIVEX_OVERRIDE_SCRIPT_SAFETY 132 
#define  URLACTION_SCRIPT_OVERRIDE_SAFETY 131 
 int URLPOLICY_DISALLOW ; 
#define  URLZONEREG_DEFAULT 130 
#define  URLZONEREG_HKCU 129 
#define  URLZONEREG_HKLM 128 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  open_zone_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,int) ; 

__attribute__((used)) static HRESULT get_action_policy(DWORD zone, DWORD action, BYTE *policy, DWORD size, URLZONEREG zone_reg)
{
    HKEY parent_key;
    HKEY hkey;
    LONG res;
    HRESULT hres;

    switch(action) {
    case URLACTION_SCRIPT_OVERRIDE_SAFETY:
    case URLACTION_ACTIVEX_OVERRIDE_SCRIPT_SAFETY:
        *(DWORD*)policy = URLPOLICY_DISALLOW;
        return S_OK;
    }

    switch(zone_reg) {
    case URLZONEREG_DEFAULT:
    case URLZONEREG_HKCU:
        parent_key = HKEY_CURRENT_USER;
        break;
    case URLZONEREG_HKLM:
        parent_key = HKEY_LOCAL_MACHINE;
        break;
    default:
        WARN("Unknown URLZONEREG: %d\n", zone_reg);
        return E_FAIL;
    };

    hres = open_zone_key(parent_key, zone, &hkey);
    if(SUCCEEDED(hres)) {
        WCHAR action_str[16];
        DWORD len = size;

        static const WCHAR formatW[] = {'%','X',0};

        wsprintfW(action_str, formatW, action);

        res = RegQueryValueExW(hkey, action_str, NULL, NULL, policy, &len);
        if(res == ERROR_MORE_DATA) {
            hres = E_INVALIDARG;
        }else if(res == ERROR_FILE_NOT_FOUND) {
            hres = E_FAIL;
        }else if(res != ERROR_SUCCESS) {
            ERR("RegQueryValue failed: %d\n", res);
            hres = E_UNEXPECTED;
        }

        RegCloseKey(hkey);
    }

    if(FAILED(hres) && zone_reg == URLZONEREG_DEFAULT)
        return get_action_policy(zone, action, policy, size, URLZONEREG_HKLM);

    return hres;
}