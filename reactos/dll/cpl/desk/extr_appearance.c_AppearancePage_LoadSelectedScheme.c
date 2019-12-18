#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ ThemeActive; } ;
struct TYPE_10__ {int /*<<< orphan*/ * crColor; } ;
struct TYPE_9__ {int /*<<< orphan*/  desktop_color; } ;
struct TYPE_8__ {TYPE_3__ Scheme; TYPE_4__ ActiveTheme; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ GLOBALS ;

/* Variables and functions */
 size_t COLOR_DESKTOP ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LoadSchemeFromReg (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  LoadSchemeFromTheme (TYPE_3__*,TYPE_4__*) ; 
 TYPE_2__ g_GlobalData ; 

__attribute__((used)) static void
AppearancePage_LoadSelectedScheme(HWND hwndDlg, GLOBALS *g)
{
    if (g->ActiveTheme.ThemeActive == FALSE )
    {
        LoadSchemeFromReg(&g->Scheme, &g->ActiveTheme);
    }
    else
    {
        LoadSchemeFromTheme(&g->Scheme, &g->ActiveTheme);
    }

    g_GlobalData.desktop_color = g->Scheme.crColor[COLOR_DESKTOP];
}