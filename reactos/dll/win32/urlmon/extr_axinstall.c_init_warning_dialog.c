#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int counter; int /*<<< orphan*/  timer; int /*<<< orphan*/  uri; } ;
typedef  TYPE_1__ install_ctx_t ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ID_AXINSTALL_ICON ; 
 int /*<<< orphan*/  ID_AXINSTALL_LOCATION ; 
 int /*<<< orphan*/  IUri_GetDisplayUri (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ LoadIconW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ OIC_WARNING ; 
 int /*<<< orphan*/  STM_SETICON ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ctxW ; 
 int /*<<< orphan*/  update_counter (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL init_warning_dialog(HWND hwnd, install_ctx_t *ctx)
{
    BSTR display_uri;
    HRESULT hres;

    if(!SetPropW(hwnd, ctxW, ctx))
        return FALSE;

    hres = IUri_GetDisplayUri(ctx->uri, &display_uri);
    if(FAILED(hres))
        return FALSE;

    SetDlgItemTextW(hwnd, ID_AXINSTALL_LOCATION, display_uri);
    SysFreeString(display_uri);

    SendDlgItemMessageW(hwnd, ID_AXINSTALL_ICON, STM_SETICON,
            (WPARAM)LoadIconW(0, (const WCHAR*)OIC_WARNING), 0);

    ctx->counter = 4;
    update_counter(ctx, hwnd);
    ctx->timer = SetTimer(hwnd, 1, 1000, NULL);
    return TRUE;
}