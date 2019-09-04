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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int /*<<< orphan*/  desktop_color; } ;
struct TYPE_7__ {int lStructSize; int Flags; int /*<<< orphan*/  rgbResult; int /*<<< orphan*/ * lpTemplateName; int /*<<< orphan*/ * lpfnHook; scalar_t__ lCustData; scalar_t__ lpCustColors; int /*<<< orphan*/ * hInstance; int /*<<< orphan*/  hwndOwner; } ;
struct TYPE_6__ {scalar_t__ custom_colors; int /*<<< orphan*/  bClrBackgroundChanged; } ;
typedef  TYPE_1__* PBACKGROUND_DATA ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;
typedef  TYPE_2__ CHOOSECOLOR ;

/* Variables and functions */
 int CC_ANYCOLOR ; 
 int CC_FULLOPEN ; 
 int CC_RGBINIT ; 
 scalar_t__ ChooseColor (TYPE_2__*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IDC_BACKGROUND_PREVIEW ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  KEY_SET_VALUE ; 
 int /*<<< orphan*/  PropSheet_Changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_BINARY ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  RegSetValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ g_GlobalData ; 

__attribute__((used)) static VOID
OnColorButton(HWND hwndDlg, PBACKGROUND_DATA pData)
{
    /* Load custom colors from Registry */
    HKEY hKey = NULL;
    LONG res = ERROR_SUCCESS;
    CHOOSECOLOR cc;

    res = RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Control Panel\\Appearance"), 0, NULL,
                         REG_OPTION_NON_VOLATILE, KEY_QUERY_VALUE, NULL, &hKey, NULL);
    /* Now the key is either created or opened existing, if res == ERROR_SUCCESS */
    if (res == ERROR_SUCCESS)
    {
        /* Key opened */
        DWORD dwType = REG_BINARY;
        DWORD cbData = sizeof(pData->custom_colors);
        res = RegQueryValueEx(hKey, TEXT("CustomColors"), NULL, &dwType,
                              (LPBYTE)pData->custom_colors, &cbData);
        RegCloseKey(hKey);
        hKey = NULL;
    }

    /* Launch ChooseColor() dialog */

    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner = hwndDlg;
    cc.hInstance = NULL;
    cc.rgbResult = g_GlobalData.desktop_color;
    cc.lpCustColors = pData->custom_colors;
    cc.Flags = CC_ANYCOLOR | /* Causes the dialog box to display all available colors in the set of basic colors.  */
               CC_FULLOPEN | /* opens dialog in full size */
               CC_RGBINIT ;  /* init chosen color by rgbResult value */
    cc.lCustData = 0;
    cc.lpfnHook = NULL;
    cc.lpTemplateName = NULL;
    if (ChooseColor(&cc))
    {
        /* Save selected color to var */
        g_GlobalData.desktop_color = cc.rgbResult;
        pData->bClrBackgroundChanged = TRUE;

        /* Apply button will be activated */
        PropSheet_Changed(GetParent(hwndDlg), hwndDlg);

        /* Window will be updated :) */
        InvalidateRect(GetDlgItem(hwndDlg, IDC_BACKGROUND_PREVIEW), NULL, TRUE);

        /* Save custom colors to reg. To this moment key must be created already. See above */
        res = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Control Panel\\Appearance"), 0,
                           KEY_SET_VALUE, &hKey);
        if (res == ERROR_SUCCESS)
        {
            /* Key opened */
            RegSetValueEx(hKey, TEXT("CustomColors"), 0, REG_BINARY,
                          (LPBYTE)pData->custom_colors, sizeof(pData->custom_colors));
            RegCloseKey(hKey);
            hKey = NULL;
        }
    }
}