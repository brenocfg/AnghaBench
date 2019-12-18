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
struct TYPE_3__ {int /*<<< orphan*/ * hthemeScrollbar; } ;
typedef  TYPE_1__* PWND_DATA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HTHEME ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseThemeData (int /*<<< orphan*/ *) ; 
 int GetThemeAppProperties () ; 
 int /*<<< orphan*/  OTD_NONCLIENT ; 
 int /*<<< orphan*/ * OpenThemeDataEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int STAP_ALLOW_NONCLIENT ; 
 TYPE_1__* ThemeGetWndData (int /*<<< orphan*/ ) ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 

HTHEME GetNCScrollbarTheme(HWND hWnd, DWORD style)
{
    PWND_DATA pwndData;

    /* We only get the theme for the scrollbar class if the window has a scrollbar */
    if((style & (WS_HSCROLL|WS_VSCROLL)) == 0)
        return NULL;

    /* Get theme data for this window */
    pwndData = ThemeGetWndData(hWnd);
    if (pwndData == NULL)
        return NULL;

    if (!(GetThemeAppProperties() & STAP_ALLOW_NONCLIENT))
    {
        if (pwndData->hthemeScrollbar)
        {
            CloseThemeData(pwndData->hthemeScrollbar);
            pwndData->hthemeScrollbar = NULL;
        }
        return NULL;
    }

    /* If the theme data was not cached, open it now */
    if (!pwndData->hthemeScrollbar)
        pwndData->hthemeScrollbar = OpenThemeDataEx(hWnd, L"SCROLLBAR", OTD_NONCLIENT);

    return pwndData->hthemeScrollbar;
}