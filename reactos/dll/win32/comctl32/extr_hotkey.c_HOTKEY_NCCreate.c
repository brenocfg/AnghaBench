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
struct TYPE_3__ {int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  strNone; int /*<<< orphan*/  CaretPos; scalar_t__ CurrMod; scalar_t__ InvMod; scalar_t__ InvComb; scalar_t__ HotKey; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ HOTKEY_INFO ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CREATESTRUCTW ;

/* Variables and functions */
 int /*<<< orphan*/  COMCTL32_hModule ; 
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKY_NONE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SM_CXBORDER ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WM_NCCREATE ; 
 int WS_EX_CLIENTEDGE ; 
 TYPE_1__* heap_alloc_zero (int) ; 

__attribute__((used)) static inline LRESULT
HOTKEY_NCCreate (HWND hwnd, const CREATESTRUCTW *lpcs)
{
    HOTKEY_INFO *infoPtr;
    DWORD dwExStyle = GetWindowLongW (hwnd, GWL_EXSTYLE);
    SetWindowLongW (hwnd, GWL_EXSTYLE, 
                    dwExStyle | WS_EX_CLIENTEDGE);

    /* allocate memory for info structure */
    infoPtr = heap_alloc_zero (sizeof(*infoPtr));
    SetWindowLongPtrW(hwnd, 0, (DWORD_PTR)infoPtr);

    /* initialize info structure */
    infoPtr->HotKey = infoPtr->InvComb = infoPtr->InvMod = infoPtr->CurrMod = 0;
    infoPtr->CaretPos = GetSystemMetrics(SM_CXBORDER);
    infoPtr->hwndSelf = hwnd;
    LoadStringW(COMCTL32_hModule, HKY_NONE, infoPtr->strNone, 15);

    return DefWindowProcW (infoPtr->hwndSelf, WM_NCCREATE, 0, (LPARAM)lpcs);
}