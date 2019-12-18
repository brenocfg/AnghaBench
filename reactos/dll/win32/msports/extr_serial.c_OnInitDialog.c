#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/ **** WCHAR ;
typedef  size_t UINT ;
struct TYPE_5__ {scalar_t__ lParam; } ;
struct TYPE_4__ {int /*<<< orphan*/  nFlowControlIndex; int /*<<< orphan*/  nStopBitsIndex; int /*<<< orphan*/  nParityIndex; int /*<<< orphan*/  nDataBitsIndex; int /*<<< orphan*/  nBaudRateIndex; } ;
typedef  TYPE_1__* PPORT_DATA ;
typedef  TYPE_2__* LPPROPSHEETPAGEW ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARRAYSIZE (int /*<<< orphan*/ *****) ; 
 int /*<<< orphan*/ ***** BaudRates ; 
 int /*<<< orphan*/  ComboBox_AddString (scalar_t__,int /*<<< orphan*/ ****) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWLP_USER ; 
 int /*<<< orphan*/ ***** DataBits ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  EnableWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillComboBox (scalar_t__,int /*<<< orphan*/ *****) ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SERIAL_ADVANCED ; 
 int /*<<< orphan*/  IDC_SERIAL_BITSPERSECOND ; 
 int /*<<< orphan*/  IDC_SERIAL_DATABITS ; 
 int /*<<< orphan*/  IDC_SERIAL_FLOWCONTROL ; 
 int /*<<< orphan*/  IDC_SERIAL_PARITY ; 
 int /*<<< orphan*/  IDC_SERIAL_STOPBITS ; 
 int /*<<< orphan*/  IDS_FLOWCONTROL ; 
 int /*<<< orphan*/  IDS_PARITY ; 
 int /*<<< orphan*/  IDS_STOPBITS ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *****,size_t) ; 
 int /*<<< orphan*/  ReadPortSettings (TYPE_1__*) ; 
 int /*<<< orphan*/  SetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ultow (int /*<<< orphan*/ ****,int /*<<< orphan*/ *****,int) ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static
BOOL
OnInitDialog(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam)
{
    PPORT_DATA pPortData;
    WCHAR szBuffer[256];
    UINT i;
    HWND hwndControl;

    TRACE("OnInitDialog()\n");

    pPortData = (PPORT_DATA)((LPPROPSHEETPAGEW)lParam)->lParam;
    if (pPortData == NULL)
    {
        ERR("pPortData is NULL\n");
        return FALSE;
    }

    SetWindowLongPtr(hwnd, DWLP_USER, (LONG_PTR)pPortData);

    /* Read and parse the port settings */
    ReadPortSettings(pPortData);

    /* Fill the 'Bits per second' combobox */
    hwndControl = GetDlgItem(hwnd, IDC_SERIAL_BITSPERSECOND);
    if (hwndControl)
    {
        for (i = 0; i < ARRAYSIZE(BaudRates); i++)
        {
            _ultow(BaudRates[i], szBuffer, 10);
            ComboBox_AddString(hwndControl, szBuffer);
        }

        ComboBox_SetCurSel(hwndControl, pPortData->nBaudRateIndex);
    }

    /* Fill the 'Data bits' combobox */
    hwndControl = GetDlgItem(hwnd, IDC_SERIAL_DATABITS);
    if (hwndControl)
    {
        for (i = 0; i < ARRAYSIZE(DataBits); i++)
        {
            ComboBox_AddString(hwndControl, DataBits[i]);
        }

        ComboBox_SetCurSel(hwndControl, pPortData->nDataBitsIndex);
    }

    /* Fill the 'Parity' combobox */
    LoadStringW(hInstance, IDS_PARITY, szBuffer, ARRAYSIZE(szBuffer));

    hwndControl = GetDlgItem(hwnd, IDC_SERIAL_PARITY);
    if (hwndControl)
    {
        FillComboBox(hwndControl, szBuffer);
        ComboBox_SetCurSel(hwndControl, pPortData->nParityIndex);
    }

    /* Fill the 'Stop bits' combobox */
    LoadStringW(hInstance, IDS_STOPBITS, szBuffer, ARRAYSIZE(szBuffer));

    hwndControl = GetDlgItem(hwnd, IDC_SERIAL_STOPBITS);
    if (hwndControl)
    {
        FillComboBox(hwndControl, szBuffer);
        ComboBox_SetCurSel(hwndControl, pPortData->nStopBitsIndex);
    }

    /* Fill the 'Flow control' combobox */
    LoadStringW(hInstance, IDS_FLOWCONTROL, szBuffer, ARRAYSIZE(szBuffer));

    hwndControl = GetDlgItem(hwnd, IDC_SERIAL_FLOWCONTROL);
    if (hwndControl)
    {
        FillComboBox(hwndControl, szBuffer);
        ComboBox_SetCurSel(hwndControl, pPortData->nFlowControlIndex);
    }

    /* Disable the 'Advanced' button */
    hwndControl = GetDlgItem(hwnd, IDC_SERIAL_ADVANCED);
    if (hwndControl)
        EnableWindow(hwndControl, FALSE);

    return TRUE;
}