#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT ;
struct TYPE_8__ {scalar_t__ hwndFrom; void* code; void* idFrom; } ;
struct TYPE_7__ {scalar_t__ hwndFrom; int /*<<< orphan*/  hwndTo; int /*<<< orphan*/  dwParam5; } ;
typedef  TYPE_1__ NOTIFYDATA ;
typedef  TYPE_2__ NMHDR ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__* LPNMHDR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 void* GetDlgCtrlID (scalar_t__) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int /*<<< orphan*/ ,void*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static LRESULT DoNotify (const NOTIFYDATA *lpNotify, UINT uCode, LPNMHDR lpHdr)
{
    NMHDR nmhdr;
    LPNMHDR lpNmh = NULL;
    UINT idFrom = 0;

    TRACE("(%p %p %d %p 0x%08x)\n",
	   lpNotify->hwndFrom, lpNotify->hwndTo, uCode, lpHdr,
	   lpNotify->dwParam5);

    if (!lpNotify->hwndTo)
	return 0;

    if (lpNotify->hwndFrom == (HWND)-1) {
	lpNmh = lpHdr;
	idFrom = lpHdr->idFrom;
    }
    else {
	if (lpNotify->hwndFrom)
	    idFrom = GetDlgCtrlID (lpNotify->hwndFrom);

	lpNmh = (lpHdr) ? lpHdr : &nmhdr;

	lpNmh->hwndFrom = lpNotify->hwndFrom;
	lpNmh->idFrom = idFrom;
	lpNmh->code = uCode;
    }

    return SendMessageW (lpNotify->hwndTo, WM_NOTIFY, idFrom, (LPARAM)lpNmh);
}