#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {void* hConn; int /*<<< orphan*/  hGeneralPage; void* hLogon; } ;
typedef  TYPE_1__* PINFO ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  FillServerAddressCombo (TYPE_1__*) ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  IDC_CONNICON ; 
 int /*<<< orphan*/  IDC_LOGONICON ; 
 int /*<<< orphan*/  IDI_CONN ; 
 int /*<<< orphan*/  IDI_LOGON ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 int /*<<< orphan*/  LR_DEFAULTCOLOR ; 
 void* LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReLoadGeneralPage (TYPE_1__*) ; 
 int /*<<< orphan*/  STM_SETICON ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOOWNERZORDER ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hInst ; 

__attribute__((used)) static VOID
GeneralOnInit(HWND hwnd,
              PINFO pInfo)
{
    SetWindowLongPtrW(hwnd,
                      GWLP_USERDATA,
                      (LONG_PTR)pInfo);

    pInfo->hGeneralPage = hwnd;

    SetWindowPos(pInfo->hGeneralPage,
                 NULL,
                 2,
                 22,
                 0,
                 0,
                 SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);

    pInfo->hLogon = LoadImageW(hInst,
                               MAKEINTRESOURCEW(IDI_LOGON),
                               IMAGE_ICON,
                               32,
                               32,
                               LR_DEFAULTCOLOR);
    if (pInfo->hLogon)
    {
        SendDlgItemMessageW(pInfo->hGeneralPage,
                            IDC_LOGONICON,
                            STM_SETICON,
                            (WPARAM)pInfo->hLogon,
                            0);
    }

    pInfo->hConn = LoadImageW(hInst,
                              MAKEINTRESOURCEW(IDI_CONN),
                              IMAGE_ICON,
                              32,
                              32,
                              LR_DEFAULTCOLOR);
    if (pInfo->hConn)
    {
        SendDlgItemMessageW(pInfo->hGeneralPage,
                            IDC_CONNICON,
                            STM_SETICON,
                            (WPARAM)pInfo->hConn,
                            0);
    }

    FillServerAddressCombo(pInfo);
    ReLoadGeneralPage(pInfo);
}