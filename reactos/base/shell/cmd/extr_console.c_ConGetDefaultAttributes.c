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
struct TYPE_3__ {int /*<<< orphan*/  wAttributes; } ;
typedef  int /*<<< orphan*/ * PWORD ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ CONSOLE_SCREEN_BUFFER_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetConsoleScreenBufferInfo (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  _T (char*) ; 

BOOL ConGetDefaultAttributes(PWORD pwDefAttr)
{
    BOOL Success;
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    /* Do not modify *pwDefAttr if we fail, in which case use default attributes */

    hConsole = CreateFile(_T("CONOUT$"), GENERIC_READ|GENERIC_WRITE,
                          FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                          OPEN_EXISTING, 0, NULL);
    if (hConsole == INVALID_HANDLE_VALUE)
        return FALSE; // No default console

    Success = GetConsoleScreenBufferInfo(hConsole, &csbi);
    if (Success)
        *pwDefAttr = csbi.wAttributes;

    CloseHandle(hConsole);
    return Success;
}