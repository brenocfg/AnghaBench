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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  key_options ; 
 scalar_t__ registry_get_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_maximized ; 

void registry_read_maximized(DWORD *bMaximized)
{
    HKEY hKey = 0;
    DWORD size = sizeof(DWORD);

    if(registry_get_handle(&hKey, 0, key_options) != ERROR_SUCCESS ||
       RegQueryValueExW(hKey, var_maximized, 0, NULL, (LPBYTE)bMaximized, &size) !=
       ERROR_SUCCESS || size != sizeof(DWORD))
    {
        *bMaximized = FALSE;
    }

    RegCloseKey(hKey);
}