#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {scalar_t__ dmDeviceName; } ;
struct TYPE_9__ {int wDeviceOffset; } ;
struct TYPE_8__ {int Flags; scalar_t__ nMaxPage; scalar_t__ nMinPage; scalar_t__ nToPage; scalar_t__ nFromPage; int /*<<< orphan*/  hDevNames; int /*<<< orphan*/  hDevMode; } ;
struct TYPE_7__ {scalar_t__ hCollateIcon; scalar_t__ hNoCollateIcon; scalar_t__ hPortraitIcon; scalar_t__ hLandscapeIcon; int /*<<< orphan*/  hwndUpDown; scalar_t__ HelpMessageID; TYPE_2__* lpPrintDlg; } ;
typedef  TYPE_1__ PRINT_PTRA ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__* LPPRINTDLGA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_3__ DEVNAMES ;
typedef  TYPE_4__ DEVMODEA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  CDERR_LOADRESFAILURE ; 
 int /*<<< orphan*/  CDERR_REGISTERMSGFAIL ; 
 int /*<<< orphan*/  COMDLG32_SetCommDlgExtendedError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMDLG32_hInstance ; 
 int /*<<< orphan*/  CreateUpDownControl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ GetDefaultPrinterA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetDlgItemTextA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HELPMSGSTRINGA ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 void* LoadIconA (int /*<<< orphan*/ ,char*) ; 
 void* LoadImageA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_COPIES ; 
 int PD_NOPAGENUMS ; 
 int PD_PRINTSETUP ; 
 int PD_SHOWHELP ; 
 int /*<<< orphan*/  PRINTDLG_ChangePrinterA (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  PRINTDLG_SetUpPrinterListComboA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegisterWindowMessageA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM_SETIMAGE ; 
 int /*<<< orphan*/  SendDlgItemMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int UDS_ALIGNRIGHT ; 
 int UDS_ARROWKEYS ; 
 int UDS_NOTHOUSANDS ; 
 int UDS_SETBUDDYINT ; 
 int /*<<< orphan*/  UPDOWN_ID ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  cmb1 ; 
 int /*<<< orphan*/  cmb4 ; 
 int /*<<< orphan*/  edt3 ; 
 int /*<<< orphan*/  ico3 ; 

__attribute__((used)) static LRESULT PRINTDLG_WMInitDialog(HWND hDlg,
				     PRINT_PTRA* PrintStructures)
{
    LPPRINTDLGA lppd = PrintStructures->lpPrintDlg;
    DEVNAMES *pdn;
    DEVMODEA *pdm;
    char *name = NULL;
    UINT comboID = (lppd->Flags & PD_PRINTSETUP) ? cmb1 : cmb4;

    /* load Collate ICONs */
    /* We load these with LoadImage because they are not a standard
       size and we don't want them rescaled */
    PrintStructures->hCollateIcon =
      LoadImageA(COMDLG32_hInstance, "PD32_COLLATE", IMAGE_ICON, 0, 0, 0);
    PrintStructures->hNoCollateIcon =
      LoadImageA(COMDLG32_hInstance, "PD32_NOCOLLATE", IMAGE_ICON, 0, 0, 0);

    /* These can be done with LoadIcon */
    PrintStructures->hPortraitIcon =
      LoadIconA(COMDLG32_hInstance, "PD32_PORTRAIT");
    PrintStructures->hLandscapeIcon =
      LoadIconA(COMDLG32_hInstance, "PD32_LANDSCAPE");

    /* display the collate/no_collate icon */
    SendDlgItemMessageA(hDlg, ico3, STM_SETIMAGE, IMAGE_ICON,
                        (LPARAM)PrintStructures->hNoCollateIcon);

    if(PrintStructures->hCollateIcon == 0 ||
       PrintStructures->hNoCollateIcon == 0 ||
       PrintStructures->hPortraitIcon == 0 ||
       PrintStructures->hLandscapeIcon == 0) {
        ERR("no icon in resource file\n");
	COMDLG32_SetCommDlgExtendedError(CDERR_LOADRESFAILURE);
	EndDialog(hDlg, FALSE);
    }

    /*
     * if lppd->Flags PD_SHOWHELP is specified, a HELPMESGSTRING message
     * must be registered and the Help button must be shown.
     */
    if (lppd->Flags & PD_SHOWHELP) {
        if((PrintStructures->HelpMessageID =
	    RegisterWindowMessageA(HELPMSGSTRINGA)) == 0) {
	    COMDLG32_SetCommDlgExtendedError(CDERR_REGISTERMSGFAIL);
	    return FALSE;
	}
    } else
        PrintStructures->HelpMessageID = 0;

    if(!(lppd->Flags &PD_PRINTSETUP)) {
        PrintStructures->hwndUpDown =
	  CreateUpDownControl(WS_CHILD | WS_VISIBLE | WS_BORDER |
			      UDS_NOTHOUSANDS | UDS_ARROWKEYS |
			      UDS_ALIGNRIGHT | UDS_SETBUDDYINT, 0, 0, 0, 0,
			      hDlg, UPDOWN_ID, COMDLG32_hInstance,
			      GetDlgItem(hDlg, edt3), MAX_COPIES, 1, 1);
    }

    /* FIXME: I allow more freedom than either Win95 or WinNT,
     *        which do not agree on what errors should be thrown or not
     *        in case nToPage or nFromPage is out-of-range.
     */
    if (lppd->nMaxPage < lppd->nMinPage)
    	lppd->nMaxPage = lppd->nMinPage;
    if (lppd->nMinPage == lppd->nMaxPage)
    	lppd->Flags |= PD_NOPAGENUMS;
    if (lppd->nToPage < lppd->nMinPage)
        lppd->nToPage = lppd->nMinPage;
    if (lppd->nToPage > lppd->nMaxPage)
        lppd->nToPage = lppd->nMaxPage;
    if (lppd->nFromPage < lppd->nMinPage)
        lppd->nFromPage = lppd->nMinPage;
    if (lppd->nFromPage > lppd->nMaxPage)
        lppd->nFromPage = lppd->nMaxPage;

    /* if we have the combo box, fill it */
    if (GetDlgItem(hDlg,comboID)) {
	/* Fill Combobox
	 */
	pdn = GlobalLock(lppd->hDevNames);
	pdm = GlobalLock(lppd->hDevMode);
	if(pdn)
	    name = (char*)pdn + pdn->wDeviceOffset;
	else if(pdm)
	    name = (char*)pdm->dmDeviceName;
	PRINTDLG_SetUpPrinterListComboA(hDlg, comboID, name);
	if(pdm) GlobalUnlock(lppd->hDevMode);
	if(pdn) GlobalUnlock(lppd->hDevNames);

	/* Now find selected printer and update rest of dlg */
	name = HeapAlloc(GetProcessHeap(),0,256);
	if (GetDlgItemTextA(hDlg, comboID, name, 255))
	    PRINTDLG_ChangePrinterA(hDlg, name, PrintStructures);
	HeapFree(GetProcessHeap(),0,name);
    } else {
	/* else use default printer */
	char name[200];
        DWORD dwBufLen = ARRAY_SIZE(name);
	BOOL ret = GetDefaultPrinterA(name, &dwBufLen);

	if (ret)
	    PRINTDLG_ChangePrinterA(hDlg, name, PrintStructures);
	else
	    FIXME("No default printer found, expect problems!\n");
    }
    return TRUE;
}