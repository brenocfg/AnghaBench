#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Size; TYPE_2__* Color; TYPE_1__* Theme; } ;
struct TYPE_9__ {TYPE_3__ ActiveTheme; } ;
struct TYPE_7__ {scalar_t__ ChildStyle; } ;
struct TYPE_6__ {scalar_t__ SizesList; } ;
typedef  scalar_t__ PTHEME_STYLE ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_4__ GLOBALS ;

/* Variables and functions */
 int /*<<< orphan*/  AppearancePage_ShowStyles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_APPEARANCE_SIZE ; 

__attribute__((used)) static void
AppearancePage_ShowSizes(HWND hwndDlg, GLOBALS *g)
{
    PTHEME_STYLE pSizes;

    if (g->ActiveTheme.Theme->SizesList)
        pSizes = g->ActiveTheme.Theme->SizesList;
    else
        pSizes = g->ActiveTheme.Color->ChildStyle;

    AppearancePage_ShowStyles(hwndDlg,
                              IDC_APPEARANCE_SIZE,
                              pSizes,
                              g->ActiveTheme.Size);
}