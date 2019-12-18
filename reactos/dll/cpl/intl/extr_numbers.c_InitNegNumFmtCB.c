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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ nNumNegFormat; int /*<<< orphan*/  szNumNegativeSign; int /*<<< orphan*/  szNumDecimalSep; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_NUMBERSNNUMFORMAT ; 
 size_t MAX_NEG_NUMBERS_SAMPLES ; 
 int /*<<< orphan*/ * ReplaceSubStr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** lpNegNumFmtSamples ; 

__attribute__((used)) static VOID
InitNegNumFmtCB(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    PWSTR pszString1, pszString2;
    INT nCBIndex;

    /* Clear all box content */
    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSNNUMFORMAT,
                        CB_RESETCONTENT,
                        (WPARAM)0,
                        (LPARAM)0);

    /* Create standard list of negative numbers formats */
    for (nCBIndex = 0; nCBIndex < MAX_NEG_NUMBERS_SAMPLES; nCBIndex++)
    {
        /* Replace standard separator to setted */
        pszString1 = ReplaceSubStr(lpNegNumFmtSamples[nCBIndex],
                                   pGlobalData->szNumDecimalSep,
                                   L",");
        if (pszString1 != NULL)
        {
            /* Replace standard negative sign to setted */
            pszString2 = ReplaceSubStr(pszString1,
                                       pGlobalData->szNumNegativeSign,
                                       L"-");
            if (pszString2 != NULL)
            {
                SendDlgItemMessageW(hwndDlg, IDC_NUMBERSNNUMFORMAT,
                                    CB_ADDSTRING,
                                    0,
                                    (LPARAM)pszString2);

                HeapFree(GetProcessHeap(), 0, pszString2);
            }

            HeapFree(GetProcessHeap(), 0, pszString1);
        }
    }

    /* Set current item to value from registry */
    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSNNUMFORMAT,
                        CB_SETCURSEL,
                        (WPARAM)pGlobalData->nNumNegFormat,
                        (LPARAM)0);
}