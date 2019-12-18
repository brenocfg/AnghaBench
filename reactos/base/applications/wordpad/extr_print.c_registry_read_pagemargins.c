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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  margins ; 
 int /*<<< orphan*/  var_pagemargin ; 

void registry_read_pagemargins(HKEY hKey)
{
    DWORD size = sizeof(RECT);

    if(!hKey || RegQueryValueExW(hKey, var_pagemargin, 0, NULL, (LPBYTE)&margins,
                     &size) != ERROR_SUCCESS || size != sizeof(RECT))
        SetRect(&margins, 1757, 1417, 1757, 1417);
}