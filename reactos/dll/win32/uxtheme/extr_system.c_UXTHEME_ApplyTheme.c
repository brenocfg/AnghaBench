#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {scalar_t__ szThemeFile; scalar_t__ pszSelectedSize; scalar_t__ pszSelectedColor; } ;
typedef  TYPE_1__* PTHEME_FILE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  UXTHEME_BackupSystemMetrics () ; 
 int /*<<< orphan*/  UXTHEME_RestoreSystemMetrics () ; 
 int /*<<< orphan*/  UXTHEME_SaveSystemMetrics () ; 
 int /*<<< orphan*/  UXTHEME_SetActiveTheme (TYPE_1__*) ; 
 scalar_t__ g_ActiveThemeFile ; 
 int lstrlenW (scalar_t__) ; 
 int /*<<< orphan*/  szColorName ; 
 int /*<<< orphan*/  szDllName ; 
 int /*<<< orphan*/  szSizeName ; 
 int /*<<< orphan*/  szThemeActive ; 
 int /*<<< orphan*/  szThemeManager ; 

__attribute__((used)) static HRESULT UXTHEME_ApplyTheme(PTHEME_FILE tf)
{
    HKEY hKey;
    WCHAR tmp[2];
    HRESULT hr;

    TRACE("UXTHEME_ApplyTheme\n");

    if (tf && !g_ActiveThemeFile)
    {
        UXTHEME_BackupSystemMetrics();
    }

    hr = UXTHEME_SetActiveTheme(tf);
    if (FAILED(hr))
        return hr;

    if (!tf) 
    {
        UXTHEME_RestoreSystemMetrics();
    }

    TRACE("Writing theme config to registry\n");
    if(!RegCreateKeyW(HKEY_CURRENT_USER, szThemeManager, &hKey)) {
        tmp[0] = g_ActiveThemeFile ? '1' : '0';
        tmp[1] = '\0';
        RegSetValueExW(hKey, szThemeActive, 0, REG_SZ, (const BYTE*)tmp, sizeof(WCHAR)*2);
        if (g_ActiveThemeFile) {
            RegSetValueExW(hKey, szColorName, 0, REG_SZ, (const BYTE*)tf->pszSelectedColor, 
		(lstrlenW(tf->pszSelectedColor)+1)*sizeof(WCHAR));
            RegSetValueExW(hKey, szSizeName, 0, REG_SZ, (const BYTE*)tf->pszSelectedSize, 
		(lstrlenW(tf->pszSelectedSize)+1)*sizeof(WCHAR));
            RegSetValueExW(hKey, szDllName, 0, REG_SZ, (const BYTE*)tf->szThemeFile, 
		(lstrlenW(tf->szThemeFile)+1)*sizeof(WCHAR));
        }
        else {
            RegDeleteValueW(hKey, szColorName);
            RegDeleteValueW(hKey, szSizeName);
            RegDeleteValueW(hKey, szDllName);

        }
        RegCloseKey(hKey);
    }
    else
        TRACE("Failed to open theme registry key\n");
    
    UXTHEME_SaveSystemMetrics ();
    
    return hr;
}