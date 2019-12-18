#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  IBindStatusCallback_iface; } ;
struct TYPE_13__ {TYPE_2__ bsc; } ;
typedef  TYPE_3__ nsChannelBSC ;
struct TYPE_11__ {int /*<<< orphan*/  IHTMLWindow2_iface; int /*<<< orphan*/ * outer_window; } ;
struct TYPE_15__ {TYPE_1__ base; TYPE_3__* bscallback; } ;
struct TYPE_14__ {TYPE_5__* pending_window; int /*<<< orphan*/  mon; } ;
typedef  TYPE_4__ HTMLOuterWindow ;
typedef  TYPE_5__ HTMLInnerWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindStatusCallback_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  abort_window_bindings (TYPE_5__*) ; 
 int /*<<< orphan*/  create_inner_window (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__**) ; 

HRESULT create_pending_window(HTMLOuterWindow *outer_window, nsChannelBSC *channelbsc)
{
    HTMLInnerWindow *pending_window;
    HRESULT hres;

    hres = create_inner_window(outer_window, outer_window->mon /* FIXME */, &pending_window);
    if(FAILED(hres))
        return hres;

    if(channelbsc) {
        IBindStatusCallback_AddRef(&channelbsc->bsc.IBindStatusCallback_iface);
        pending_window->bscallback = channelbsc;
    }

    if(outer_window->pending_window) {
        abort_window_bindings(outer_window->pending_window);
        outer_window->pending_window->base.outer_window = NULL;
        IHTMLWindow2_Release(&outer_window->pending_window->base.IHTMLWindow2_iface);
    }

    outer_window->pending_window = pending_window;
    return S_OK;
}