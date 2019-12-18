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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  WarrantyCaption; int /*<<< orphan*/  Warranty; } ;
typedef  TYPE_1__ LICENSE ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ WineLicense_En ; 

VOID WineWarranty(HWND Wnd)
{
    /* FIXME: should load strings from resources */
    LICENSE *License = &WineLicense_En;
    MessageBoxA(Wnd,
                License->Warranty,
                License->WarrantyCaption,
                MB_ICONEXCLAMATION | MB_OK);
}