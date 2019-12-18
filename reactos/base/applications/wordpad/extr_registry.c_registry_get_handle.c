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
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LPDWORD ;
typedef  char* LPCWSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,char const*) ; 
 int lstrlenW (char const*) ; 

__attribute__((used)) static LRESULT registry_get_handle(HKEY *hKey, LPDWORD action, LPCWSTR subKey)
{
    LONG ret;
    static const WCHAR wszProgramKey[] = {'S','o','f','t','w','a','r','e','\\',
        'M','i','c','r','o','s','o','f','t','\\',
        'W','i','n','d','o','w','s','\\',
        'C','u','r','r','e','n','t','V','e','r','s','i','o','n','\\',
        'A','p','p','l','e','t','s','\\',
        'W','o','r','d','p','a','d',0};
        LPWSTR key = (LPWSTR)wszProgramKey;

        if(subKey)
        {
            WCHAR backslash[] = {'\\',0};
            key = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                            (lstrlenW(wszProgramKey)+lstrlenW(subKey)+lstrlenW(backslash)+1)
                                    *sizeof(WCHAR));

            if(!key)
                return 1;

            lstrcpyW(key, wszProgramKey);
            lstrcatW(key, backslash);
            lstrcatW(key, subKey);
        }

        if(action)
        {
            ret = RegCreateKeyExW(HKEY_CURRENT_USER, key, 0, NULL, REG_OPTION_NON_VOLATILE,
                                  KEY_READ | KEY_WRITE, NULL, hKey, action);
        } else
        {
            ret = RegOpenKeyExW(HKEY_CURRENT_USER, key, 0, KEY_READ | KEY_WRITE, hKey);
        }

        if(subKey)
            HeapFree(GetProcessHeap(), 0, key);

        return ret;
}