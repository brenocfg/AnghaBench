#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int /*<<< orphan*/  pRdpSettings; int /*<<< orphan*/  hGeneralPage; int /*<<< orphan*/  hDisplayPage; TYPE_2__* DisplayDeviceList; } ;
struct TYPE_6__ {TYPE_1__* Resolutions; } ;
struct TYPE_5__ {int dmPelsWidth; int dmPelsHeight; } ;
typedef  TYPE_3__* PINFO ;
typedef  int INT ;

/* Variables and functions */
 int CB_ERR ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 scalar_t__ GetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IDC_BPPCOMBO ; 
 int /*<<< orphan*/  IDC_GEOSLIDER ; 
 int /*<<< orphan*/  IDC_NAMEEDIT ; 
 int /*<<< orphan*/  IDC_SERVERCOMBO ; 
 int MAXVALUE ; 
 int SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetIntegerToSettings (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SetStringToSettings (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TBM_GETPOS ; 
 int /*<<< orphan*/  TBM_GETRANGEMAX ; 

VOID
SaveAllSettings(PINFO pInfo)
{
    INT ret;
    WCHAR szValue[MAXVALUE];

    /* server */
    if (GetDlgItemText(pInfo->hGeneralPage,
                       IDC_SERVERCOMBO,
                       szValue,
                       MAXVALUE))
    {
        SetStringToSettings(pInfo->pRdpSettings,
                            L"full address",
                            szValue);
    }

    /* resolution and fullscreen*/
    ret = SendDlgItemMessage(pInfo->hDisplayPage,
                             IDC_GEOSLIDER,
                             TBM_GETPOS,
                             0,
                             0);
    if (ret != -1)
    {
        SetIntegerToSettings(pInfo->pRdpSettings,
                             L"screen mode id",
                             (ret == SendDlgItemMessageW(pInfo->hDisplayPage, IDC_GEOSLIDER, TBM_GETRANGEMAX, 0, 0)) ? 2 : 1);
        SetIntegerToSettings(pInfo->pRdpSettings,
                             L"desktopwidth",
                             pInfo->DisplayDeviceList->Resolutions[ret].dmPelsWidth);
        SetIntegerToSettings(pInfo->pRdpSettings,
                             L"desktopheight",
                             pInfo->DisplayDeviceList->Resolutions[ret].dmPelsHeight);
    }

    /* bpp */
    ret = SendDlgItemMessage(pInfo->hDisplayPage,
                             IDC_BPPCOMBO,
                             CB_GETCURSEL,
                             0,
                             0);
    if (ret != CB_ERR)
    {
        ret = SendDlgItemMessage(pInfo->hDisplayPage,
                                 IDC_BPPCOMBO,
                                 CB_GETITEMDATA,
                                 ret,
                                 0);
        if (ret != CB_ERR)
        {
            SetIntegerToSettings(pInfo->pRdpSettings,
                                 L"session bpp",
                                 ret);
        }
    }

    /* user name */
    if (GetDlgItemText(pInfo->hGeneralPage,
                       IDC_NAMEEDIT,
                       szValue,
                       MAXVALUE))
    {
        SetStringToSettings(pInfo->pRdpSettings,
                            L"username",
                            szValue);
    }
}