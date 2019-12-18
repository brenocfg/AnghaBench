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
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CREATESTRUCTW ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NCCREATE ; 
 int /*<<< orphan*/  WS_EX_CLIENTEDGE ; 

__attribute__((used)) static LRESULT
DATETIME_NCCreate (HWND hwnd, const CREATESTRUCTW *lpcs)
{
    DWORD dwExStyle = GetWindowLongW(hwnd, GWL_EXSTYLE);
    /* force control to have client edge */
    dwExStyle |= WS_EX_CLIENTEDGE;
    SetWindowLongW(hwnd, GWL_EXSTYLE, dwExStyle);

    return DefWindowProcW(hwnd, WM_NCCREATE, 0, (LPARAM)lpcs);
}