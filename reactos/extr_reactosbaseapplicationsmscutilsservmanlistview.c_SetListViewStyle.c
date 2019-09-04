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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LVS_TYPEMASK ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

VOID
SetListViewStyle(HWND hListView,
                 DWORD View)
{
    DWORD Style = GetWindowLongPtr(hListView, GWL_STYLE);

    if ((Style & LVS_TYPEMASK) != View)
    {
        SetWindowLongPtr(hListView,
                         GWL_STYLE,
                         (Style & ~LVS_TYPEMASK) | View);
    }
}