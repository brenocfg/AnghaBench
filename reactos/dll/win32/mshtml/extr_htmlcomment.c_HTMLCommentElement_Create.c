#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNode ;
struct TYPE_11__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_9__ {TYPE_6__ node; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {TYPE_2__ element; TYPE_1__ IHTMLCommentElement_iface; } ;
typedef  TYPE_2__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  TYPE_3__ HTMLCommentElement ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLCommentElementImplVtbl ; 
 int /*<<< orphan*/  HTMLCommentElementVtbl ; 
 int /*<<< orphan*/  HTMLCommentElement_dispex ; 
 int /*<<< orphan*/  HTMLDOMNode_Init (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLElement_Init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* heap_alloc_zero (int) ; 

HRESULT HTMLCommentElement_Create(HTMLDocumentNode *doc, nsIDOMNode *nsnode, HTMLElement **elem)
{
    HTMLCommentElement *ret;

    ret = heap_alloc_zero(sizeof(*ret));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->element.node.vtbl = &HTMLCommentElementImplVtbl;
    ret->IHTMLCommentElement_iface.lpVtbl = &HTMLCommentElementVtbl;

    HTMLElement_Init(&ret->element, doc, NULL, &HTMLCommentElement_dispex);
    HTMLDOMNode_Init(doc, &ret->element.node, nsnode);

    *elem = &ret->element;
    return S_OK;
}