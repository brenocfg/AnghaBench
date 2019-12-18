#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_12__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_15__ {TYPE_3__ node; } ;
struct TYPE_16__ {TYPE_6__ element; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {TYPE_9__ framebase; TYPE_2__ IHTMLIFrameElement3_iface; TYPE_1__ IHTMLIFrameElement2_iface; TYPE_4__ IHTMLIFrameElement_iface; } ;
typedef  TYPE_5__ HTMLIFrame ;
typedef  TYPE_6__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLFrameBase_Init (TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLIFrameElement2Vtbl ; 
 int /*<<< orphan*/  HTMLIFrameElement3Vtbl ; 
 int /*<<< orphan*/  HTMLIFrameElementVtbl ; 
 int /*<<< orphan*/  HTMLIFrameImplVtbl ; 
 int /*<<< orphan*/  HTMLIFrame_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_5__* heap_alloc_zero (int) ; 

HRESULT HTMLIFrame_Create(HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem, HTMLElement **elem)
{
    HTMLIFrame *ret;

    ret = heap_alloc_zero(sizeof(HTMLIFrame));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IHTMLIFrameElement_iface.lpVtbl = &HTMLIFrameElementVtbl;
    ret->IHTMLIFrameElement2_iface.lpVtbl = &HTMLIFrameElement2Vtbl;
    ret->IHTMLIFrameElement3_iface.lpVtbl = &HTMLIFrameElement3Vtbl;
    ret->framebase.element.node.vtbl = &HTMLIFrameImplVtbl;

    HTMLFrameBase_Init(&ret->framebase, doc, nselem, &HTMLIFrame_dispex);

    *elem = &ret->framebase.element;
    return S_OK;
}