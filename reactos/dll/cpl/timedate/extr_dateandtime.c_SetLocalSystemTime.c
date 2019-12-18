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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DWLP_MSGRESULT ; 
 scalar_t__ DateTime_GetSystemtime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GDT_VALID ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HWND_BROADCAST ; 
 int /*<<< orphan*/  IDC_MONTHCALENDAR ; 
 int /*<<< orphan*/  IDC_TIMEPICKER ; 
 int /*<<< orphan*/  MCCM_GETDATE ; 
 int /*<<< orphan*/  MCCM_RESET ; 
 int /*<<< orphan*/  PSNRET_NOERROR ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemSetLocalTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM_TIMECHANGE ; 

__attribute__((used)) static VOID
SetLocalSystemTime(HWND hwnd)
{
    SYSTEMTIME Time;

    if (DateTime_GetSystemtime(GetDlgItem(hwnd,
                                          IDC_TIMEPICKER),
                               &Time) == GDT_VALID &&
        SendMessageW(GetDlgItem(hwnd,
                                IDC_MONTHCALENDAR),
                     MCCM_GETDATE,
                     (WPARAM)&Time,
                     0))
    {
        SystemSetLocalTime(&Time);

        SetWindowLongPtrW(hwnd,
                          DWLP_MSGRESULT,
                          PSNRET_NOERROR);

        SendMessageW(GetDlgItem(hwnd,
                                IDC_MONTHCALENDAR),
                     MCCM_RESET,
                     (WPARAM)&Time,
                     0);

        /* Broadcast the time change message */
        SendMessageW(HWND_BROADCAST,
                     WM_TIMECHANGE,
                     0,
                     0);
    }
}