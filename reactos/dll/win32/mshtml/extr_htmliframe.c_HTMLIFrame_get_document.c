#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* content_window; } ;
struct TYPE_15__ {TYPE_6__ framebase; } ;
struct TYPE_12__ {TYPE_3__* inner_window; } ;
struct TYPE_13__ {TYPE_4__ base; } ;
struct TYPE_11__ {TYPE_2__* doc; } ;
struct TYPE_9__ {int /*<<< orphan*/  IHTMLDocument2_iface; } ;
struct TYPE_10__ {TYPE_1__ basedoc; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_7__ HTMLIFrame ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_7__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLIFrame_get_document(HTMLDOMNode *iface, IDispatch **p)
{
    HTMLIFrame *This = impl_from_HTMLDOMNode(iface);

    if(!This->framebase.content_window || !This->framebase.content_window->base.inner_window->doc) {
        *p = NULL;
        return S_OK;
    }

    *p = (IDispatch*)&This->framebase.content_window->base.inner_window->doc->basedoc.IHTMLDocument2_iface;
    IDispatch_AddRef(*p);
    return S_OK;
}