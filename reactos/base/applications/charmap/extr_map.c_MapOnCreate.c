#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int cx; int cy; } ;
struct TYPE_10__ {int cx; int cy; } ;
struct TYPE_13__ {void* hParent; int /*<<< orphan*/ * pActiveCell; TYPE_2__ ClientSize; TYPE_1__ CellSize; void* hMapWnd; } ;
struct TYPE_12__ {int right; int bottom; } ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__* PMAP ;
typedef  int /*<<< orphan*/  MAP ;
typedef  void* HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (void*,TYPE_3__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  SetGrid (TYPE_4__*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetScrollPos (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int XCELLS ; 
 int YCELLS ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 

__attribute__((used)) static
BOOL
MapOnCreate(PMAP infoPtr,
            HWND hwnd,
            HWND hParent)
{
    RECT rc;
    BOOL Ret = FALSE;

    infoPtr = HeapAlloc(GetProcessHeap(),
                        0,
                        sizeof(MAP));
    if (infoPtr)
    {
        SetLastError(0);
        SetWindowLongPtrW(hwnd,
                          0,
                          (DWORD_PTR)infoPtr);
        if (GetLastError() == 0)
        {
            ZeroMemory(infoPtr,
                       sizeof(MAP));

            infoPtr->hMapWnd = hwnd;
            infoPtr->hParent = hParent;

            GetClientRect(hwnd, &rc);
            infoPtr->ClientSize.cx = rc.right;
            infoPtr->ClientSize.cy = rc.bottom;
            infoPtr->CellSize.cx = infoPtr->ClientSize.cx / XCELLS;
            infoPtr->CellSize.cy = infoPtr->ClientSize.cy / YCELLS;

            infoPtr->pActiveCell = NULL;

            SetGrid(infoPtr);

            SetScrollPos(infoPtr->hParent, SB_VERT, 0, TRUE);

            Ret = TRUE;
        }
    }

    return Ret;
}