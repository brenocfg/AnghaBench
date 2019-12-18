#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int UINT16 ;
struct TYPE_11__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_10__ {TYPE_2__ node; } ;
typedef  TYPE_1__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  TYPE_2__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
#define  ATTRIBUTE_NODE 132 
#define  COMMENT_NODE 131 
#define  DOCUMENT_TYPE_NODE 130 
#define  ELEMENT_NODE 129 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HTMLCommentElement_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  HTMLDOMNodeImplVtbl ; 
 int /*<<< orphan*/  HTMLDOMNode_Init (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLDOMTextNode_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  HTMLElement_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  S_OK ; 
#define  TEXT_NODE 128 
 int /*<<< orphan*/  TRACE (char*,int,TYPE_2__*) ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  nsIDOMNode_GetNodeType (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static HRESULT create_node(HTMLDocumentNode *doc, nsIDOMNode *nsnode, HTMLDOMNode **ret)
{
    UINT16 node_type;
    HRESULT hres;

    nsIDOMNode_GetNodeType(nsnode, &node_type);

    switch(node_type) {
    case ELEMENT_NODE: {
        HTMLElement *elem;
        hres = HTMLElement_Create(doc, nsnode, FALSE, &elem);
        if(FAILED(hres))
            return hres;
        *ret = &elem->node;
        break;
    }
    case TEXT_NODE:
        hres = HTMLDOMTextNode_Create(doc, nsnode, ret);
        if(FAILED(hres))
            return hres;
        break;
    /* doctype nodes are represented as comment nodes (at least in quirks mode) */
    case DOCUMENT_TYPE_NODE:
    case COMMENT_NODE: {
        HTMLElement *comment;
        hres = HTMLCommentElement_Create(doc, nsnode, &comment);
        if(FAILED(hres))
            return hres;
        *ret = &comment->node;
        break;
    }
    case ATTRIBUTE_NODE:
        ERR("Called on attribute node\n");
        return E_UNEXPECTED;
    default: {
        HTMLDOMNode *node;

        node = heap_alloc_zero(sizeof(HTMLDOMNode));
        if(!node)
            return E_OUTOFMEMORY;

        node->vtbl = &HTMLDOMNodeImplVtbl;
        HTMLDOMNode_Init(doc, node, nsnode);
        *ret = node;
    }
    }

    TRACE("type %d ret %p\n", node_type, *ret);
    return S_OK;
}