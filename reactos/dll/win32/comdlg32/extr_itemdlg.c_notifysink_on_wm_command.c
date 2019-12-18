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
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  FileDialogImpl ;

/* Variables and functions */
#define  BN_CLICKED 129 
#define  CBN_SELCHANGE 128 
 int /*<<< orphan*/  FALSE ; 
 int HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifysink_on_bn_clicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifysink_on_cbn_selchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT notifysink_on_wm_command(FileDialogImpl *This, HWND hwnd, WPARAM wparam, LPARAM lparam)
{
    switch(HIWORD(wparam))
    {
    case BN_CLICKED:          return notifysink_on_bn_clicked(This, hwnd, wparam);
    case CBN_SELCHANGE:       return notifysink_on_cbn_selchange(This, hwnd, wparam);
    }

    return FALSE;
}