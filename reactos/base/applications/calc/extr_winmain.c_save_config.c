#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osvi ;
struct TYPE_5__ {int /*<<< orphan*/  usesep; int /*<<< orphan*/  layout; } ;
struct TYPE_4__ {int dwOSVersionInfoSize; int dwPlatformId; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ OSVERSIONINFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetVersionEx (TYPE_1__*) ; 
 int /*<<< orphan*/  SaveRegInt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  VER_PLATFORM_WIN32_WINDOWS 129 
#define  VER_PLATFORM_WIN32s 128 
 int /*<<< orphan*/  WriteProfileString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _T (char*) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ calc ; 

__attribute__((used)) static void save_config(void)
{
    TCHAR buf[32];
    OSVERSIONINFO osvi;

    osvi.dwOSVersionInfoSize = sizeof(osvi);
    GetVersionEx(&osvi);

    switch (osvi.dwPlatformId) {
    case VER_PLATFORM_WIN32s:
    case VER_PLATFORM_WIN32_WINDOWS:
        _stprintf(buf, _T("%lu"), calc.layout);
        WriteProfileString(_T("SciCalc"), _T("layout"), buf);
        WriteProfileString(_T("SciCalc"), _T("UseSep"), (calc.usesep==TRUE) ? _T("1") : _T("0"));
        break;

    default: /* VER_PLATFORM_WIN32_NT */
        SaveRegInt(_T("SOFTWARE\\Microsoft\\Calc"), _T("layout"), calc.layout);
        SaveRegInt(_T("SOFTWARE\\Microsoft\\Calc"), _T("UseSep"), calc.usesep);
        break;
    }
}