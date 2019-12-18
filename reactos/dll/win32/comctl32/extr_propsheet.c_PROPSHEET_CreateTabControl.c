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
struct TYPE_7__ {int nPages; TYPE_1__* proppage; scalar_t__ hImageList; } ;
struct TYPE_6__ {scalar_t__ pszText; int /*<<< orphan*/  mask; int /*<<< orphan*/  iImage; int /*<<< orphan*/  cchTextMax; } ;
struct TYPE_5__ {scalar_t__ pszText; scalar_t__ hasIcon; } ;
typedef  TYPE_2__ TCITEMW ;
typedef  TYPE_3__ PropSheetInfo ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_TABCONTROL ; 
 int /*<<< orphan*/  MAX_TABTEXT_LENGTH ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCIF_IMAGE ; 
 int /*<<< orphan*/  TCIF_TEXT ; 
 int /*<<< orphan*/  TCM_INSERTITEMW ; 
 int /*<<< orphan*/  TCM_SETIMAGELIST ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETREDRAW ; 

__attribute__((used)) static BOOL PROPSHEET_CreateTabControl(HWND hwndParent,
                                       const PropSheetInfo * psInfo)
{
  HWND hwndTabCtrl = GetDlgItem(hwndParent, IDC_TABCONTROL);
  TCITEMW item;
  int i, nTabs;
  int iImage = 0;

  TRACE("\n");
  item.mask = TCIF_TEXT;
  item.cchTextMax = MAX_TABTEXT_LENGTH;

  nTabs = psInfo->nPages;

  /*
   * Set the image list for icons.
   */
  if (psInfo->hImageList)
  {
    SendMessageW(hwndTabCtrl, TCM_SETIMAGELIST, 0, (LPARAM)psInfo->hImageList);
  }

  SendMessageW(hwndTabCtrl, WM_SETREDRAW, 0, 0);
  for (i = 0; i < nTabs; i++)
  {
    if ( psInfo->proppage[i].hasIcon )
    {
      item.mask |= TCIF_IMAGE;
      item.iImage = iImage++;
    }
    else
    {
      item.mask &= ~TCIF_IMAGE;
    }

    item.pszText = (LPWSTR) psInfo->proppage[i].pszText;
    SendMessageW(hwndTabCtrl, TCM_INSERTITEMW, i, (LPARAM)&item);
  }
  SendMessageW(hwndTabCtrl, WM_SETREDRAW, 1, 0);

  return TRUE;
}