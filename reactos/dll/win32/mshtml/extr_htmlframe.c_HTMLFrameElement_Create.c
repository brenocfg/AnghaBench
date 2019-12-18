#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
struct TYPE_8__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_11__ {TYPE_1__ node; } ;
struct TYPE_12__ {TYPE_4__ element; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {TYPE_7__ framebase; TYPE_2__ IHTMLFrameElement3_iface; } ;
typedef  TYPE_3__ HTMLFrameElement ;
typedef  TYPE_4__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLFrameBase_Init (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLFrameElement3Vtbl ; 
 int /*<<< orphan*/  HTMLFrameElementImplVtbl ; 
 int /*<<< orphan*/  HTMLFrameElement_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* heap_alloc_zero (int) ; 

HRESULT HTMLFrameElement_Create(HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem, HTMLElement **elem)
{
    HTMLFrameElement *ret;

    ret = heap_alloc_zero(sizeof(HTMLFrameElement));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->framebase.element.node.vtbl = &HTMLFrameElementImplVtbl;
    ret->IHTMLFrameElement3_iface.lpVtbl = &HTMLFrameElement3Vtbl;

    HTMLFrameBase_Init(&ret->framebase, doc, nselem, &HTMLFrameElement_dispex);

    *elem = &ret->framebase.element;
    return S_OK;
}