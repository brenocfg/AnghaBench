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
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ szNumThousandSep; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 size_t CB_ERR ; 
 int /*<<< orphan*/  CB_LIMITTEXT ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CB_SELECTSTRING ; 
 int /*<<< orphan*/  IDC_NUMBERSDIGITGRSYM ; 
 size_t MAX_FIELD_SEP_SAMPLES ; 
 int MAX_NUMTHOUSANDSEP ; 
 size_t SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__* lpFieldSepSamples ; 

__attribute__((used)) static VOID
InitNumFieldSepCB(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    INT nCBIndex;
    INT nRetCode;

    /* Limit text length */
    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSDIGITGRSYM,
                        CB_LIMITTEXT,
                        MAX_NUMTHOUSANDSEP - 1,
                        0);

    /* Clear all box content */
    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSDIGITGRSYM,
                        CB_RESETCONTENT,
                        (WPARAM)0,
                        (LPARAM)0);

    /* Create standard list of field separators */
    for (nCBIndex = 0; nCBIndex < MAX_FIELD_SEP_SAMPLES; nCBIndex++)
    {
        SendDlgItemMessageW(hwndDlg, IDC_NUMBERSDIGITGRSYM,
                            CB_ADDSTRING,
                            0,
                            (LPARAM)lpFieldSepSamples[nCBIndex]);
    }

    /* Set current item to value from registry */
    nRetCode = SendDlgItemMessageW(hwndDlg, IDC_NUMBERSDIGITGRSYM,
                                   CB_SELECTSTRING,
                                   -1,
                                   (LPARAM)pGlobalData->szNumThousandSep);

    /* If it is not success, add new values to list and select them */
    if (nRetCode == CB_ERR)
    {
        SendDlgItemMessageW(hwndDlg, IDC_NUMBERSDIGITGRSYM,
                            CB_ADDSTRING,
                            0,
                            (LPARAM)pGlobalData->szNumThousandSep);
        SendDlgItemMessageW(hwndDlg, IDC_NUMBERSDIGITGRSYM,
                            CB_SELECTSTRING,
                            -1,
                            (LPARAM)pGlobalData->szNumThousandSep);
    }
}