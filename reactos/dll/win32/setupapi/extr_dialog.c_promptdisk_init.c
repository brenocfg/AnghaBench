#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  unknown ;
struct promptdisk_params {int DiskPromptStyle; scalar_t__ DiskName; scalar_t__ FileSought; int /*<<< orphan*/ * PathToSource; scalar_t__ DialogTitle; } ;
typedef  int /*<<< orphan*/  message ;
typedef  int /*<<< orphan*/  format ;
typedef  int /*<<< orphan*/  __ms_va_list ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  DWLP_USER ; 
 int FORMAT_MESSAGE_ARGUMENT_ARRAY ; 
 int FORMAT_MESSAGE_FROM_STRING ; 
 int /*<<< orphan*/  FormatMessageW (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_COPYFROM ; 
 int /*<<< orphan*/  IDC_FILENEEDED ; 
 int /*<<< orphan*/  IDC_INFO ; 
 int /*<<< orphan*/  IDC_PATH ; 
 int /*<<< orphan*/  IDC_RUNDLG_BROWSE ; 
 int IDF_NOBROWSE ; 
 int IDF_OEMDISK ; 
 int /*<<< orphan*/  IDS_COPYFROM ; 
 int /*<<< orphan*/  IDS_INFO ; 
 int /*<<< orphan*/  IDS_PROMPTDISK ; 
 int /*<<< orphan*/  IDS_UNKNOWN ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static void promptdisk_init(HWND hwnd, struct promptdisk_params *params)
{
    SetWindowLongPtrW(hwnd, DWLP_USER, (LONG_PTR)params);

    if(params->DialogTitle)
        SetWindowTextW(hwnd, params->DialogTitle);
    if(params->PathToSource)
        SetDlgItemTextW(hwnd, IDC_PATH, params->PathToSource);

    if(!(params->DiskPromptStyle & IDF_OEMDISK))
    {
        WCHAR message[256+2*MAX_PATH];
        WCHAR format[256];
        WCHAR unknown[256];
        DWORD_PTR args[2];
        LoadStringW(hInstance, IDS_PROMPTDISK, format,
            sizeof(format)/sizeof(format[0]));

        args[0] = (DWORD_PTR)params->FileSought;
        if(params->DiskName)
            args[1] = (DWORD_PTR)params->DiskName;
        else
        {
            LoadStringW(hInstance, IDS_UNKNOWN, unknown,
                sizeof(unknown)/sizeof(unknown[0]));
            args[1] = (DWORD_PTR)unknown;
        }
        FormatMessageW(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ARGUMENT_ARRAY,
                       format, 0, 0, message, sizeof(message)/sizeof(*message),
                       (__ms_va_list*)args);
        SetDlgItemTextW(hwnd, IDC_FILENEEDED, message);

        LoadStringW(hInstance, IDS_INFO, message,
            sizeof(message)/sizeof(message[0]));
        SetDlgItemTextW(hwnd, IDC_INFO, message);
        LoadStringW(hInstance, IDS_COPYFROM, message,
            sizeof(message)/sizeof(message[0]));
        SetDlgItemTextW(hwnd, IDC_COPYFROM, message);
    }
    if(params->DiskPromptStyle & IDF_NOBROWSE)
        ShowWindow(GetDlgItem(hwnd, IDC_RUNDLG_BROWSE), SW_HIDE);
}