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
struct TYPE_5__ {void* is_memory; void* usesep; int /*<<< orphan*/  layout; } ;
struct TYPE_4__ {int dwOSVersionInfoSize; int dwPlatformId; } ;
typedef  TYPE_1__ OSVERSIONINFO ;

/* Variables and functions */
 void* CALC_LAYOUT_STANDARD ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetProfileInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  GetVersionEx (TYPE_1__*) ; 
 int /*<<< orphan*/  LoadRegInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  UpdateNumberIntl () ; 
#define  VER_PLATFORM_WIN32_WINDOWS 129 
#define  VER_PLATFORM_WIN32s 128 
 int /*<<< orphan*/  _T (char*) ; 
 TYPE_2__ calc ; 

__attribute__((used)) static void load_config(void)
{
    OSVERSIONINFO osvi;

    osvi.dwOSVersionInfoSize = sizeof(osvi);
    GetVersionEx(&osvi);

    switch (osvi.dwPlatformId) {
    case VER_PLATFORM_WIN32s:
    case VER_PLATFORM_WIN32_WINDOWS:
        /* Try to load last selected layout */
        calc.layout = GetProfileInt(_T("SciCalc"), _T("layout"), CALC_LAYOUT_STANDARD);

        /* Try to load last selected formatting option */
        calc.usesep = (GetProfileInt(_T("SciCalc"), _T("UseSep"), FALSE)) ? TRUE : FALSE;
        break;

    default: /* VER_PLATFORM_WIN32_NT */
        /* Try to load last selected layout */
        calc.layout = LoadRegInt(_T("SOFTWARE\\Microsoft\\Calc"), _T("layout"), CALC_LAYOUT_STANDARD);

        /* Try to load last selected formatting option */
        calc.usesep = (LoadRegInt(_T("SOFTWARE\\Microsoft\\Calc"), _T("UseSep"), FALSE)) ? TRUE : FALSE;
        break;
    }

    /* memory is empty at startup */
    calc.is_memory = FALSE;

    /* Get locale info for numbers */
    UpdateNumberIntl();
}