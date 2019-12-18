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
typedef  int /*<<< orphan*/  szFormat ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int dmDisplayFrequency; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PDEVMODEW ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IDES_REFRESHRATEFMT ; 
 int /*<<< orphan*/  IDS_DEFREFRESHRATE ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEXT (char) ; 
 int /*<<< orphan*/  _sntprintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static VOID
GetRefreshRateDescription(PDEVMODEW lpDevMode,
                          LPTSTR lpBuffer,
                          DWORD dwBufferLen)
{
    TCHAR szFormat[64];

    if (lpDevMode->dmDisplayFrequency <= 1)
    {
        if (!LoadString(hInstance,
                        IDS_DEFREFRESHRATE,
                        lpBuffer,
                        dwBufferLen))
        {
            lpBuffer[0] = TEXT('\0');
        }
    }
    else
    {
        if (!LoadString(hInstance,
                        IDES_REFRESHRATEFMT,
                        szFormat,
                        sizeof(szFormat) / sizeof(szFormat[0])))
        {
            szFormat[0] = TEXT('\0');
        }

        _sntprintf(lpBuffer,
                   dwBufferLen,
                   szFormat,
                   lpDevMode->dmDisplayFrequency);
    }
}