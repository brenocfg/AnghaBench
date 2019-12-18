#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {int dmCopies; scalar_t__ dmOrientation; } ;
struct TYPE_14__ {TYPE_1__ s1; } ;
struct TYPE_17__ {int dmFields; int /*<<< orphan*/  pPortName; int /*<<< orphan*/ * pPrinterName; TYPE_2__ u1; int /*<<< orphan*/  dmDeviceName; } ;
struct TYPE_16__ {scalar_t__ hDevMode; int Flags; int nFromPage; int nToPage; int nCopies; } ;
struct TYPE_15__ {scalar_t__ hLandscapeIcon; scalar_t__ hPortraitIcon; TYPE_5__* lpPrinterInfo; scalar_t__ hNoCollateIcon; scalar_t__ hCollateIcon; TYPE_5__* lpDevMode; TYPE_5__* lpDriverInfo; TYPE_4__* lpPrintDlg; } ;
typedef  TYPE_3__ PRINT_PTRW ;
typedef  TYPE_4__* LPPRINTDLGW ;
typedef  TYPE_5__* LPDEVMODEW ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int LONG ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CheckRadioButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClosePrinter (int /*<<< orphan*/ ) ; 
 scalar_t__ DMORIENT_PORTRAIT ; 
 int DM_COLLATE ; 
 int DM_COPIES ; 
 int DM_IN_BUFFER ; 
 int DM_OUT_BUFFER ; 
 int DocumentPropertiesW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPrinterDriverW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  GetPrinterW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_5__* GlobalLock (scalar_t__) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 int MAX_COPIES ; 
 int /*<<< orphan*/  OpenPrinterW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PD_COLLATE ; 
 int PD_DISABLEPRINTTOFILE ; 
 int PD_HIDEPRINTTOFILE ; 
 int PD_NOPAGENUMS ; 
 int PD_NOSELECTION ; 
 int PD_PAGENUMS ; 
 int PD_PRINTSETUP ; 
 int PD_PRINTTOFILE ; 
 int PD_SELECTION ; 
 int PD_SHOWHELP ; 
 int PD_USEDEVMODECOPIESANDCOLLATE ; 
 int /*<<< orphan*/  PRINTDLG_SetUpPaperComboBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  PRINTDLG_UpdatePrinterInfoTextsW (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  STM_SETIMAGE ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  chx1 ; 
 int /*<<< orphan*/  chx2 ; 
 int /*<<< orphan*/  cmb2 ; 
 int /*<<< orphan*/  cmb3 ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edt1 ; 
 int /*<<< orphan*/  edt2 ; 
 int /*<<< orphan*/  edt3 ; 
 int /*<<< orphan*/  ico1 ; 
 int /*<<< orphan*/  ico3 ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pshHelp ; 
 int /*<<< orphan*/  rad1 ; 
 int /*<<< orphan*/  rad2 ; 
 int /*<<< orphan*/  rad3 ; 
 int /*<<< orphan*/  stc2 ; 
 int /*<<< orphan*/  stc3 ; 
 int /*<<< orphan*/  stc5 ; 

__attribute__((used)) static BOOL PRINTDLG_ChangePrinterW(HWND hDlg, WCHAR *name,
				   PRINT_PTRW *PrintStructures)
{
    LPPRINTDLGW lppd = PrintStructures->lpPrintDlg;
    LPDEVMODEW lpdm = NULL;
    LONG dmSize;
    DWORD needed;
    HANDLE hprn;

    HeapFree(GetProcessHeap(),0, PrintStructures->lpPrinterInfo);
    HeapFree(GetProcessHeap(),0, PrintStructures->lpDriverInfo);
    if(!OpenPrinterW(name, &hprn, NULL)) {
        ERR("Can't open printer %s\n", debugstr_w(name));
	return FALSE;
    }
    GetPrinterW(hprn, 2, NULL, 0, &needed);
    PrintStructures->lpPrinterInfo = HeapAlloc(GetProcessHeap(),0,needed);
    GetPrinterW(hprn, 2, (LPBYTE)PrintStructures->lpPrinterInfo, needed,
		&needed);
    GetPrinterDriverW(hprn, NULL, 3, NULL, 0, &needed);
    PrintStructures->lpDriverInfo = HeapAlloc(GetProcessHeap(),0,needed);
    if (!GetPrinterDriverW(hprn, NULL, 3, (LPBYTE)PrintStructures->lpDriverInfo,
	    needed, &needed)) {
	ERR("GetPrinterDriverA failed for %s, fix your config!\n",debugstr_w(PrintStructures->lpPrinterInfo->pPrinterName));
	return FALSE;
    }
    ClosePrinter(hprn);

    PRINTDLG_UpdatePrinterInfoTextsW(hDlg, PrintStructures->lpPrinterInfo);

    HeapFree(GetProcessHeap(), 0, PrintStructures->lpDevMode);
    PrintStructures->lpDevMode = NULL;

    dmSize = DocumentPropertiesW(0, 0, name, NULL, NULL, 0);
    if(dmSize == -1) {
        ERR("DocumentProperties fails on %s\n", debugstr_w(name));
	return FALSE;
    }
    PrintStructures->lpDevMode = HeapAlloc(GetProcessHeap(), 0, dmSize);
    dmSize = DocumentPropertiesW(0, 0, name, PrintStructures->lpDevMode, NULL,
				 DM_OUT_BUFFER);
    if(lppd->hDevMode && (lpdm = GlobalLock(lppd->hDevMode)) &&
			  !lstrcmpW(lpdm->dmDeviceName,
				  PrintStructures->lpDevMode->dmDeviceName)) {
      /* Supplied devicemode matches current printer so try to use it */
        DocumentPropertiesW(0, 0, name, PrintStructures->lpDevMode, lpdm,
			    DM_OUT_BUFFER | DM_IN_BUFFER);
    }
    if(lpdm)
        GlobalUnlock(lppd->hDevMode);

    lpdm = PrintStructures->lpDevMode;  /* use this as a shortcut */

    if(!(lppd->Flags & PD_PRINTSETUP)) {
	/* Print range (All/Range/Selection) */
	if(lppd->nFromPage != 0xffff)
	    SetDlgItemInt(hDlg, edt1, lppd->nFromPage, FALSE);
	if(lppd->nToPage != 0xffff)
	    SetDlgItemInt(hDlg, edt2, lppd->nToPage, FALSE);

	CheckRadioButton(hDlg, rad1, rad3, rad1);		/* default */
	if (lppd->Flags & PD_NOSELECTION)
	    EnableWindow(GetDlgItem(hDlg, rad2), FALSE);
	else
	    if (lppd->Flags & PD_SELECTION)
	        CheckRadioButton(hDlg, rad1, rad3, rad2);
	if (lppd->Flags & PD_NOPAGENUMS) {
	    EnableWindow(GetDlgItem(hDlg, rad3), FALSE);
	    EnableWindow(GetDlgItem(hDlg, stc2),FALSE);
	    EnableWindow(GetDlgItem(hDlg, edt1), FALSE);
	    EnableWindow(GetDlgItem(hDlg, stc3),FALSE);
	    EnableWindow(GetDlgItem(hDlg, edt2), FALSE);
	} else {
	    if (lppd->Flags & PD_PAGENUMS)
	        CheckRadioButton(hDlg, rad1, rad3, rad3);
	}

	/* Collate pages
	 *
	 * FIXME: The ico3 is not displayed for some reason. I don't know why.
	 */
	if (lppd->Flags & PD_COLLATE) {
            SendDlgItemMessageW(hDlg, ico3, STM_SETIMAGE, IMAGE_ICON,
				(LPARAM)PrintStructures->hCollateIcon);
	    CheckDlgButton(hDlg, chx2, 1);
	} else {
            SendDlgItemMessageW(hDlg, ico3, STM_SETIMAGE, IMAGE_ICON,
				(LPARAM)PrintStructures->hNoCollateIcon);
	    CheckDlgButton(hDlg, chx2, 0);
	}

	if (lppd->Flags & PD_USEDEVMODECOPIESANDCOLLATE) {
	  /* if printer doesn't support it: no Collate */
	    if (!(lpdm->dmFields & DM_COLLATE)) {
	        EnableWindow(GetDlgItem(hDlg, chx2), FALSE);
		EnableWindow(GetDlgItem(hDlg, ico3), FALSE);
	    }
	}

	/* nCopies */
	{
	  INT copies;
	  if (lppd->hDevMode == 0)
	      copies = lppd->nCopies;
	  else
	      copies = lpdm->u1.s1.dmCopies;
	  if(copies == 0) copies = 1;
	  else if(copies < 0) copies = MAX_COPIES;
	  SetDlgItemInt(hDlg, edt3, copies, FALSE);
	}

	if (lppd->Flags & PD_USEDEVMODECOPIESANDCOLLATE) {
	  /* if printer doesn't support it: no nCopies */
	    if (!(lpdm->dmFields & DM_COPIES)) {
	        EnableWindow(GetDlgItem(hDlg, edt3), FALSE);
		EnableWindow(GetDlgItem(hDlg, stc5), FALSE);
	    }
	}

	/* print to file */
	CheckDlgButton(hDlg, chx1, (lppd->Flags & PD_PRINTTOFILE) ? 1 : 0);
	if (lppd->Flags & PD_DISABLEPRINTTOFILE)
            EnableWindow(GetDlgItem(hDlg, chx1), FALSE);
	if (lppd->Flags & PD_HIDEPRINTTOFILE)
            ShowWindow(GetDlgItem(hDlg, chx1), SW_HIDE);

    } else { /* PD_PRINTSETUP */
      BOOL bPortrait = (lpdm->u1.s1.dmOrientation == DMORIENT_PORTRAIT);

      PRINTDLG_SetUpPaperComboBoxW(hDlg, cmb2,
				  PrintStructures->lpPrinterInfo->pPrinterName,
				  PrintStructures->lpPrinterInfo->pPortName,
				  lpdm);
      PRINTDLG_SetUpPaperComboBoxW(hDlg, cmb3,
				  PrintStructures->lpPrinterInfo->pPrinterName,
				  PrintStructures->lpPrinterInfo->pPortName,
				  lpdm);
      CheckRadioButton(hDlg, rad1, rad2, bPortrait ? rad1: rad2);
      SendDlgItemMessageW(hDlg, ico1, STM_SETIMAGE, IMAGE_ICON,
                          (LPARAM)(bPortrait ? PrintStructures->hPortraitIcon :
                                   PrintStructures->hLandscapeIcon));

    }

    /* help button */
    if ((lppd->Flags & PD_SHOWHELP)==0) {
        /* hide if PD_SHOWHELP not specified */
        ShowWindow(GetDlgItem(hDlg, pshHelp), SW_HIDE);
    }
    return TRUE;
}