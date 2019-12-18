#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_8__ {TYPE_2__* content_window; } ;
struct TYPE_9__ {TYPE_3__ framebase; } ;
struct TYPE_6__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  IServiceProvider ;
typedef  TYPE_4__ HTMLIFrame ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  int /*<<< orphan*/  DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IDispatchEx_InvokeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLIFrame_invoke(HTMLDOMNode *iface, DISPID id, LCID lcid,
        WORD flags, DISPPARAMS *params, VARIANT *res, EXCEPINFO *ei, IServiceProvider *caller)
{
    HTMLIFrame *This = impl_from_HTMLDOMNode(iface);

    if(!This->framebase.content_window) {
        ERR("no content window to invoke on\n");
        return E_FAIL;
    }

    return IDispatchEx_InvokeEx(&This->framebase.content_window->base.IDispatchEx_iface, id, lcid,
            flags, params, res, ei, caller);
}