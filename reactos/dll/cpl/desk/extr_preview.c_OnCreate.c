#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  Scheme; int /*<<< orphan*/  lpButText; int /*<<< orphan*/  lpMessText; int /*<<< orphan*/  lpMessBox; int /*<<< orphan*/  lpWinTxt; int /*<<< orphan*/  lpAct; int /*<<< orphan*/  lpInAct; int /*<<< orphan*/  hMenu; scalar_t__ hClientFont; } ;
typedef  TYPE_1__* PPREVIEW_DATA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  COLOR_SCHEME ;

/* Variables and functions */
 int /*<<< orphan*/  AllocAndLoadString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_GUI_FONT ; 
 int /*<<< orphan*/  EnableMenuItem (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HiliteMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  IDR_PREVIEW_MENU ; 
 int /*<<< orphan*/  IDS_ACTWIN ; 
 int /*<<< orphan*/  IDS_BUTTEXT ; 
 int /*<<< orphan*/  IDS_INACTWIN ; 
 int /*<<< orphan*/  IDS_MESSBOX ; 
 int /*<<< orphan*/  IDS_MESSTEXT ; 
 int /*<<< orphan*/  IDS_WINTEXT ; 
 int /*<<< orphan*/  LoadCurrentScheme (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int MF_BYPOSITION ; 
 int MF_GRAYED ; 
 int MF_HILITE ; 
 int /*<<< orphan*/  UpdatePreviewTheme (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static VOID
OnCreate(HWND hwnd, PPREVIEW_DATA pPreviewData)
{
    COLOR_SCHEME *scheme;

    pPreviewData->hClientFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

    /* Load and modify the menu */
    pPreviewData->hMenu = LoadMenu(hApplet, MAKEINTRESOURCE(IDR_PREVIEW_MENU));
    EnableMenuItem(pPreviewData->hMenu,
                   1, MF_BYPOSITION | MF_GRAYED);
    HiliteMenuItem(hwnd, pPreviewData->hMenu,
                   2, MF_BYPOSITION | MF_HILITE);

//    GetMenuItemRect(hwnd, pPreviewData->hMenu,
//                    2, &pPreviewData->rcSelectedMenuItem);

    AllocAndLoadString(&pPreviewData->lpInAct, hApplet, IDS_INACTWIN);
    AllocAndLoadString(&pPreviewData->lpAct, hApplet, IDS_ACTWIN);
    AllocAndLoadString(&pPreviewData->lpWinTxt, hApplet, IDS_WINTEXT);
    AllocAndLoadString(&pPreviewData->lpMessBox, hApplet, IDS_MESSBOX);
    AllocAndLoadString(&pPreviewData->lpMessText, hApplet, IDS_MESSTEXT);
    AllocAndLoadString(&pPreviewData->lpButText, hApplet, IDS_BUTTEXT);

    scheme = &pPreviewData->Scheme;
    LoadCurrentScheme(scheme);

    UpdatePreviewTheme(hwnd, pPreviewData, scheme);
}