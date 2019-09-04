#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int bMenuAnimation; int bFontSmoothing; int bDropShadow; int bDragFullWindows; int bKeyboardCues; } ;
struct TYPE_7__ {scalar_t__ bFlatMenus; TYPE_1__ Effects; } ;
struct TYPE_8__ {TYPE_2__ SchemeAdv; TYPE_2__ Scheme; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_3__ GLOBALS ;

/* Variables and functions */
 int /*<<< orphan*/  AddToCombobox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BM_SETCHECK ; 
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  BST_UNCHECKED ; 
 int /*<<< orphan*/  EffAppearanceDlgUpdateControls (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ IDC_EFFAPPEARANCE_ANIMATION ; 
 int /*<<< orphan*/  IDC_EFFAPPEARANCE_ANIMATIONTYPE ; 
 scalar_t__ IDC_EFFAPPEARANCE_DRAGFULLWINDOWS ; 
 scalar_t__ IDC_EFFAPPEARANCE_FLATMENUS ; 
 scalar_t__ IDC_EFFAPPEARANCE_KEYBOARDCUES ; 
 scalar_t__ IDC_EFFAPPEARANCE_SETDROPSHADOW ; 
 scalar_t__ IDC_EFFAPPEARANCE_SMOOTHING ; 
 int /*<<< orphan*/  IDC_EFFAPPEARANCE_SMOOTHINGTYPE ; 
 int /*<<< orphan*/  IDS_CLEARTYPEEFFECT ; 
 int /*<<< orphan*/  IDS_FADEEFFECT ; 
 int /*<<< orphan*/  IDS_SLIDEEFFECT ; 
 int /*<<< orphan*/  IDS_STANDARDEFFECT ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static VOID
EffAppearanceDlg_Init(HWND hwndDlg, GLOBALS *g)
{
    WPARAM state;

    /* Copy the current theme values */
    g->SchemeAdv = g->Scheme;

#define INIT_CHECKBOX(__CONTROL_ID, __MEMBER)                           \
do { \
    state = /* Do a XOR of both the conditions */                       \
        ((g->SchemeAdv.Effects.__MEMBER) != (__CONTROL_ID == IDC_EFFAPPEARANCE_KEYBOARDCUES)) \
            ? BST_CHECKED : BST_UNCHECKED;                              \
    SendDlgItemMessageW(hwndDlg, __CONTROL_ID, BM_SETCHECK, state, 0);  \
} while(0)

#define INIT_CHECKBOX_SCH(__CONTROL_ID, __MEMBER)                       \
do { \
    state = /* Do a XOR of both the conditions */                       \
        ((g->SchemeAdv.__MEMBER) == TRUE)                               \
            ? BST_CHECKED : BST_UNCHECKED;                              \
    SendDlgItemMessageW(hwndDlg, __CONTROL_ID, BM_SETCHECK, state, 0);  \
} while(0)

#define FILL_COMBOBOX(__CONTROL_ID, __FIRST_STR, __LAST_STR) \
    AddToCombobox(__CONTROL_ID, hwndDlg, __FIRST_STR, __LAST_STR)

    /* Animated menu transitions section (checkbox + combo) */
    INIT_CHECKBOX(IDC_EFFAPPEARANCE_ANIMATION,       bMenuAnimation);
    FILL_COMBOBOX(IDC_EFFAPPEARANCE_ANIMATIONTYPE,   IDS_SLIDEEFFECT,
                                                     IDS_FADEEFFECT);

    /* Font antialiasing section (checkbox + combo) */
    INIT_CHECKBOX(IDC_EFFAPPEARANCE_SMOOTHING,       bFontSmoothing);
    FILL_COMBOBOX(IDC_EFFAPPEARANCE_SMOOTHINGTYPE,   IDS_STANDARDEFFECT,
                                                     IDS_CLEARTYPEEFFECT);

    /* Other checkboxes */
    INIT_CHECKBOX(IDC_EFFAPPEARANCE_SETDROPSHADOW,   bDropShadow);
    INIT_CHECKBOX(IDC_EFFAPPEARANCE_DRAGFULLWINDOWS, bDragFullWindows);
    INIT_CHECKBOX(IDC_EFFAPPEARANCE_KEYBOARDCUES,    bKeyboardCues);
    INIT_CHECKBOX_SCH(IDC_EFFAPPEARANCE_FLATMENUS,   bFlatMenus);

#undef INIT_CHECKBOX
#undef FILL_COMBOBOX

    /* Update the controls */
    EffAppearanceDlgUpdateControls(hwndDlg, g);
}