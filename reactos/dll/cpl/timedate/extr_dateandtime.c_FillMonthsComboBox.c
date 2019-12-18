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
typedef  int /*<<< orphan*/  szBuf ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_3__ {scalar_t__ wMonth; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int CB_ERR ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int /*<<< orphan*/  GetLocalTime (TYPE_1__*) ; 
 int GetLocaleInfoW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ LOCALE_SMONTHNAME1 ; 
 scalar_t__ LOCALE_SMONTHNAME13 ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VOID
FillMonthsComboBox(HWND hCombo)
{
    SYSTEMTIME LocalDate = {0};
    WCHAR szBuf[64];
    INT i;
    UINT Month;

    GetLocalTime(&LocalDate);

    SendMessageW(hCombo,
                 CB_RESETCONTENT,
                 0,
                 0);

    for (Month = 1;
         Month <= 13;
         Month++)
    {
        i = GetLocaleInfoW(LOCALE_USER_DEFAULT,
                           ((Month < 13) ? LOCALE_SMONTHNAME1 + Month - 1 : LOCALE_SMONTHNAME13),
                           szBuf,
                           sizeof(szBuf) / sizeof(szBuf[0]));
        if (i > 1)
        {
            i = (INT)SendMessageW(hCombo,
                                  CB_ADDSTRING,
                                  0,
                                  (LPARAM)szBuf);
            if (i != CB_ERR)
            {
                SendMessageW(hCombo,
                             CB_SETITEMDATA,
                             (WPARAM)i,
                             Month);

                if (Month == (UINT)LocalDate.wMonth)
                {
                    SendMessageW(hCombo,
                                 CB_SETCURSEL,
                                 (WPARAM)i,
                                 0);
                }
            }
        }
    }
}