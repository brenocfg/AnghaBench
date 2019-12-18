#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_8__ {int /*<<< orphan*/  iHeight; int /*<<< orphan*/  iWidth; TYPE_1__ hdr; int /*<<< orphan*/  dwFlag; } ;
struct TYPE_7__ {int dwStyle; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  nHeight; int /*<<< orphan*/  nWidth; int /*<<< orphan*/  hwndNotify; } ;
typedef  TYPE_2__ PAGER_INFO ;
typedef  TYPE_3__ NMPGCALCSIZE ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGF_CALCHEIGHT ; 
 int /*<<< orphan*/  PGF_CALCWIDTH ; 
 int /*<<< orphan*/  PGN_CALCSIZE ; 
 int PGS_HORZ ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 

__attribute__((used)) static void
PAGER_CalcSize( PAGER_INFO *infoPtr )
{
    NMPGCALCSIZE nmpgcs;
    ZeroMemory (&nmpgcs, sizeof (NMPGCALCSIZE));
    nmpgcs.hdr.hwndFrom = infoPtr->hwndSelf;
    nmpgcs.hdr.idFrom   = GetWindowLongPtrW (infoPtr->hwndSelf, GWLP_ID);
    nmpgcs.hdr.code = PGN_CALCSIZE;
    nmpgcs.dwFlag = (infoPtr->dwStyle & PGS_HORZ) ? PGF_CALCWIDTH : PGF_CALCHEIGHT;
    nmpgcs.iWidth = infoPtr->nWidth;
    nmpgcs.iHeight = infoPtr->nHeight;
    SendMessageW (infoPtr->hwndNotify, WM_NOTIFY, nmpgcs.hdr.idFrom, (LPARAM)&nmpgcs);

    if (infoPtr->dwStyle & PGS_HORZ)
        infoPtr->nWidth = nmpgcs.iWidth;
    else
        infoPtr->nHeight = nmpgcs.iHeight;

    TRACE("[%p] PGN_CALCSIZE returns %dx%d\n", infoPtr->hwndSelf, nmpgcs.iWidth, nmpgcs.iHeight );
}