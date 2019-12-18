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
struct TYPE_7__ {int /*<<< orphan*/  hwnd; TYPE_2__* ofnA; TYPE_1__* ofnW; } ;
struct TYPE_6__ {int nMaxFileTitle; scalar_t__* lpstrFileTitle; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpstrFileTitle; } ;
typedef  TYPE_1__* LPOPENFILENAMEW ;
typedef  TYPE_2__* LPOPENFILENAMEA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_3__ FD31_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lst1 ; 

__attribute__((used)) static void FD31_UpdateFileTitle(const FD31_DATA *lfs)
{
  LONG lRet;
  LPOPENFILENAMEW ofnW = lfs->ofnW;
  LPOPENFILENAMEA ofnA = lfs->ofnA;

  if (ofnW->lpstrFileTitle != NULL)
  {
    lRet = SendDlgItemMessageW(lfs->hwnd, lst1, LB_GETCURSEL, 0, 0);
    SendDlgItemMessageW(lfs->hwnd, lst1, LB_GETTEXT, lRet,
                             (LPARAM)ofnW->lpstrFileTitle );
    if (ofnA)
    {
        if (!WideCharToMultiByte( CP_ACP, 0, ofnW->lpstrFileTitle, -1,
                                  ofnA->lpstrFileTitle, ofnA->nMaxFileTitle, NULL, NULL ))
            ofnA->lpstrFileTitle[ofnA->nMaxFileTitle-1] = 0;
    }
  }
}