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
typedef  scalar_t__ WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int bMenuAnimation; int bFontSmoothing; int bDropShadow; int bDragFullWindows; int bKeyboardCues; scalar_t__ uiFontSmoothingType; scalar_t__ bMenuFade; } ;
struct TYPE_6__ {int bFlatMenus; TYPE_1__ Effects; } ;
struct TYPE_7__ {int /*<<< orphan*/  bSchemeChanged; TYPE_2__ SchemeAdv; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_3__ GLOBALS ;

/* Variables and functions */
 int /*<<< orphan*/  BM_GETCHECK ; 
 scalar_t__ BST_CHECKED ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IDC_EFFAPPEARANCE_ANIMATION ; 
 scalar_t__ IDC_EFFAPPEARANCE_ANIMATIONTYPE ; 
 scalar_t__ IDC_EFFAPPEARANCE_DRAGFULLWINDOWS ; 
 scalar_t__ IDC_EFFAPPEARANCE_FLATMENUS ; 
 scalar_t__ IDC_EFFAPPEARANCE_KEYBOARDCUES ; 
 scalar_t__ IDC_EFFAPPEARANCE_SETDROPSHADOW ; 
 scalar_t__ IDC_EFFAPPEARANCE_SMOOTHING ; 
 scalar_t__ IDC_EFFAPPEARANCE_SMOOTHINGTYPE ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static VOID
EffAppearanceDlgUpdateControls(HWND hwndDlg, GLOBALS *g)
{
    WPARAM state;

#define SAVE_CHECKBOX(__CONTROL_ID, __MEMBER)                               \
do { \
    state = SendDlgItemMessageW(hwndDlg, __CONTROL_ID, BM_GETCHECK, 0, 0);  \
    g->SchemeAdv.Effects.__MEMBER = /* Do a XOR of both the conditions */   \
        ((state == BST_CHECKED) != (__CONTROL_ID == IDC_EFFAPPEARANCE_KEYBOARDCUES)); \
} while(0)

#define SAVE_CHECKBOX_SCH(__CONTROL_ID, __MEMBER)                           \
do { \
    state = SendDlgItemMessageW(hwndDlg, __CONTROL_ID, BM_GETCHECK, 0, 0);  \
    g->SchemeAdv.__MEMBER = (state == BST_CHECKED);                         \
} while(0)

#define RSET_COMBOBOX(__CONTROL_ID, __PARENT_MEMBER, __MEMBER)                                          \
do { \
    SendDlgItemMessageW(hwndDlg, __CONTROL_ID, CB_SETCURSEL, (WPARAM)g->SchemeAdv.Effects.__MEMBER, 0); \
    EnableWindow(GetDlgItem(hwndDlg, __CONTROL_ID), g->SchemeAdv.Effects.__PARENT_MEMBER);              \
} while(0)

    /* Animated menu transitions section (checkbox + combo) */
    SAVE_CHECKBOX(IDC_EFFAPPEARANCE_ANIMATION,       bMenuAnimation);
    RSET_COMBOBOX(IDC_EFFAPPEARANCE_ANIMATIONTYPE,   bMenuAnimation, bMenuFade);

    /* Font antialiasing section (checkbox + combo) */
    SAVE_CHECKBOX(IDC_EFFAPPEARANCE_SMOOTHING,       bFontSmoothing);
    RSET_COMBOBOX(IDC_EFFAPPEARANCE_SMOOTHINGTYPE,   bFontSmoothing, uiFontSmoothingType - 1);

    /* Other checkboxes */
    SAVE_CHECKBOX(IDC_EFFAPPEARANCE_SETDROPSHADOW,   bDropShadow);
    SAVE_CHECKBOX(IDC_EFFAPPEARANCE_DRAGFULLWINDOWS, bDragFullWindows);
    SAVE_CHECKBOX(IDC_EFFAPPEARANCE_KEYBOARDCUES,    bKeyboardCues);
    SAVE_CHECKBOX_SCH(IDC_EFFAPPEARANCE_FLATMENUS,   bFlatMenus);

#undef SAVE_CHECKBOX
#undef RSET_COMBOBOX

    g->bSchemeChanged = TRUE;
}