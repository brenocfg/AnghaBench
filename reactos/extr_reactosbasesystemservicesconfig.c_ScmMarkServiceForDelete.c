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
struct TYPE_3__ {int /*<<< orphan*/  lpServiceName; } ;
typedef  TYPE_1__* PSERVICE ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ScmOpenServiceKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

DWORD
ScmMarkServiceForDelete(PSERVICE pService)
{
    HKEY hServiceKey = NULL;
    DWORD dwValue = 1;
    DWORD dwError;

    DPRINT("ScmMarkServiceForDelete() called\n");

    dwError = ScmOpenServiceKey(pService->lpServiceName,
                                KEY_WRITE,
                                &hServiceKey);
    if (dwError != ERROR_SUCCESS)
        return dwError;

    dwError = RegSetValueExW(hServiceKey,
                             L"DeleteFlag",
                             0,
                             REG_DWORD,
                             (LPBYTE)&dwValue,
                             sizeof(DWORD));

    RegCloseKey(hServiceKey);

    return dwError;
}