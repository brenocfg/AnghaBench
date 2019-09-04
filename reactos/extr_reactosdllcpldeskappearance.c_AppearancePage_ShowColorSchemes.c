#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Color; TYPE_1__* Theme; } ;
struct TYPE_7__ {TYPE_2__ ActiveTheme; } ;
struct TYPE_5__ {int /*<<< orphan*/  ColoursList; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_3__ GLOBALS ;

/* Variables and functions */
 int /*<<< orphan*/  AppearancePage_ShowStyles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_APPEARANCE_COLORSCHEME ; 

__attribute__((used)) static void
AppearancePage_ShowColorSchemes(HWND hwndDlg, GLOBALS *g)
{
    AppearancePage_ShowStyles(hwndDlg,
                              IDC_APPEARANCE_COLORSCHEME,
                              g->ActiveTheme.Theme->ColoursList,
                              g->ActiveTheme.Color);
}