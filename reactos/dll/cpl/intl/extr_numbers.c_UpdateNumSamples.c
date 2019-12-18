#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int /*<<< orphan*/  nInteger; } ;
struct TYPE_7__ {int /*<<< orphan*/  NegativeOrder; int /*<<< orphan*/  lpThousandSep; int /*<<< orphan*/  lpDecimalSep; int /*<<< orphan*/  Grouping; int /*<<< orphan*/  LeadingZero; int /*<<< orphan*/  NumDigits; } ;
struct TYPE_6__ {size_t nNumGrouping; int /*<<< orphan*/  UserLCID; int /*<<< orphan*/  nNumNegFormat; int /*<<< orphan*/  szNumThousandSep; int /*<<< orphan*/  szNumDecimalSep; int /*<<< orphan*/  nNumLeadingZero; int /*<<< orphan*/  nNumDigits; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  TYPE_2__ NUMBERFMT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetNumberFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* GroupingFormats ; 
 int /*<<< orphan*/  IDC_NUMBERSNEGSAMPLE ; 
 int /*<<< orphan*/  IDC_NUMBERSPOSSAMPLE ; 
 int MAX_FMT_SIZE ; 
 int /*<<< orphan*/  SAMPLE_NEG_NUMBER ; 
 int /*<<< orphan*/  SAMPLE_NUMBER ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 

__attribute__((used)) static VOID
UpdateNumSamples(HWND hwndDlg,
                 PGLOBALDATA pGlobalData)
{
    WCHAR OutBuffer[MAX_FMT_SIZE];
    NUMBERFMT NumberFormat;

    NumberFormat.NumDigits = pGlobalData->nNumDigits;
    NumberFormat.LeadingZero = pGlobalData->nNumLeadingZero;
    NumberFormat.Grouping = GroupingFormats[pGlobalData->nNumGrouping].nInteger;
    NumberFormat.lpDecimalSep = pGlobalData->szNumDecimalSep;
    NumberFormat.lpThousandSep = pGlobalData->szNumThousandSep;
    NumberFormat.NegativeOrder = pGlobalData->nNumNegFormat;

    /* Get positive number format sample */
    GetNumberFormatW(pGlobalData->UserLCID,
                     0,
                     SAMPLE_NUMBER,
                     &NumberFormat,
                     OutBuffer,
                     MAX_FMT_SIZE);

    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSPOSSAMPLE,
                        WM_SETTEXT,
                        0,
                        (LPARAM)OutBuffer);

    /* Get positive number format sample */
    GetNumberFormatW(pGlobalData->UserLCID,
                     0,
                     SAMPLE_NEG_NUMBER,
                     &NumberFormat,
                     OutBuffer,
                     MAX_FMT_SIZE);

    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSNEGSAMPLE,
                        WM_SETTEXT,
                        0,
                        (LPARAM)OutBuffer);
}