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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WNDPROC ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT_PTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CallWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MAKEINTATOM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atSubclassProp ; 
 int /*<<< orphan*/ * originalProcs ; 

LRESULT THEMING_CallOriginalClass (HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    INT_PTR subclass = (INT_PTR)GetPropW (wnd, (LPCWSTR)MAKEINTATOM(atSubclassProp));
    WNDPROC oldProc = originalProcs[subclass];
    return CallWindowProcW (oldProc, wnd, msg, wParam, lParam);
}