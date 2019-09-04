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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  Control_RunDLLW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  SW_SHOW ; 

__attribute__((used)) static INT
RunControlPanel(LPCWSTR lpCmd)
{
    /*
     * Old method:
     *
    WCHAR szParameters[MAX_PATH];
    wcscpy(szParameters, L"shell32.dll,Control_RunDLL ");
    wcscat(szParameters, lpCmd);
    return RUNDLL(szParameters);
     */

    /* New method: */
    Control_RunDLLW(GetDesktopWindow(), 0, lpCmd, SW_SHOW);
    return 1;
}