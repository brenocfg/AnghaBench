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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int style; scalar_t__ hwndSelf; int /*<<< orphan*/  bEnableState; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 scalar_t__ DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ES_READONLY ; 
 int /*<<< orphan*/  GetParent (scalar_t__) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_CTLCOLOREDIT ; 
 int /*<<< orphan*/  WM_CTLCOLORSTATIC ; 

__attribute__((used)) static HBRUSH EDIT_NotifyCtlColor(EDITSTATE *es, HDC hdc)
{
    HBRUSH hbrush;
    UINT msg;

    if ((!es->bEnableState || (es->style & ES_READONLY)))
        msg = WM_CTLCOLORSTATIC;
    else
        msg = WM_CTLCOLOREDIT;

    /* Why do we notify to es->hwndParent, and we send this one to GetParent()? */
    hbrush = (HBRUSH)SendMessageW(GetParent(es->hwndSelf), msg, (WPARAM)hdc, (LPARAM)es->hwndSelf);
    if (!hbrush)
        hbrush = (HBRUSH)DefWindowProcW(GetParent(es->hwndSelf), msg, (WPARAM)hdc, (LPARAM)es->hwndSelf);
    return hbrush;
}