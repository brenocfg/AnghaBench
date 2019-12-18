#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNode ;
struct TYPE_14__ {int /*<<< orphan*/ * cp_container; int /*<<< orphan*/ * vtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/  IHTMLWindow2_iface; } ;
struct TYPE_13__ {TYPE_2__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/  cp_container; int /*<<< orphan*/  doc_obj; } ;
struct TYPE_12__ {TYPE_1__ basedoc; TYPE_9__ node; TYPE_7__* window; } ;
typedef  TYPE_3__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLDOMNode_Init (TYPE_3__*,TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLDocumentFragmentImplVtbl ; 
 int /*<<< orphan*/  IHTMLWindow2_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* alloc_doc_node (int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static HRESULT create_document_fragment(nsIDOMNode *nsnode, HTMLDocumentNode *doc_node, HTMLDocumentNode **ret)
{
    HTMLDocumentNode *doc_frag;

    doc_frag = alloc_doc_node(doc_node->basedoc.doc_obj, doc_node->window);
    if(!doc_frag)
        return E_OUTOFMEMORY;

    IHTMLWindow2_AddRef(&doc_frag->window->base.IHTMLWindow2_iface);

    HTMLDOMNode_Init(doc_node, &doc_frag->node, nsnode);
    doc_frag->node.vtbl = &HTMLDocumentFragmentImplVtbl;
    doc_frag->node.cp_container = &doc_frag->basedoc.cp_container;

    *ret = doc_frag;
    return S_OK;
}