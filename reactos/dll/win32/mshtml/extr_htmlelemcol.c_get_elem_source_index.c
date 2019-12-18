#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
struct TYPE_12__ {int member_2; int size; int len; TYPE_3__** buf; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ elem_vector_t ;
typedef  scalar_t__ UINT16 ;
struct TYPE_14__ {int /*<<< orphan*/  IHTMLDOMNode_iface; } ;
struct TYPE_11__ {int /*<<< orphan*/  doc; int /*<<< orphan*/ * nsnode; } ;
struct TYPE_13__ {TYPE_1__ node; } ;
typedef  int LONG ;
typedef  TYPE_3__ HTMLElement ;
typedef  TYPE_4__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ DOCUMENT_FRAGMENT_NODE ; 
 scalar_t__ DOCUMENT_NODE ; 
 scalar_t__ ELEMENT_NODE ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IHTMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  create_all_list (int /*<<< orphan*/ ,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**) ; 
 TYPE_3__** heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_3__**) ; 
 int /*<<< orphan*/  nsIDOMNode_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_GetNodeType (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsIDOMNode_GetParentNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 

HRESULT get_elem_source_index(HTMLElement *elem, LONG *ret)
{
    elem_vector_t buf = {NULL, 0, 8};
    nsIDOMNode *parent_node, *iter;
    UINT16 parent_type;
    HTMLDOMNode *node;
    int i;
    nsresult nsres;
    HRESULT hres;

    iter = elem->node.nsnode;
    nsIDOMNode_AddRef(iter);

    /* Find document or document fragment parent. */
    while(1) {
        nsres = nsIDOMNode_GetParentNode(iter, &parent_node);
        nsIDOMNode_Release(iter);
        assert(nsres == NS_OK);
        if(!parent_node)
            break;

        nsres = nsIDOMNode_GetNodeType(parent_node, &parent_type);
        assert(nsres == NS_OK);

        if(parent_type != ELEMENT_NODE) {
            if(parent_type != DOCUMENT_NODE && parent_type != DOCUMENT_FRAGMENT_NODE)
                FIXME("Unexpected parent_type %d\n", parent_type);
            break;
        }

        iter = parent_node;
    }

    if(!parent_node) {
        *ret = -1;
        return S_OK;
    }

    hres = get_node(elem->node.doc, parent_node, TRUE, &node);
    nsIDOMNode_Release(parent_node);
    if(FAILED(hres))
        return hres;


    /* Create all children collection and find the element in it.
     * This could be optimized if we ever find the reason. */
    buf.buf = heap_alloc(buf.size*sizeof(*buf.buf));
    if(!buf.buf) {
        IHTMLDOMNode_Release(&node->IHTMLDOMNode_iface);
        return E_OUTOFMEMORY;
    }

    create_all_list(elem->node.doc, node, &buf);

    for(i=0; i < buf.len; i++) {
        if(buf.buf[i] == elem)
            break;
    }
    IHTMLDOMNode_Release(&node->IHTMLDOMNode_iface);
    heap_free(buf.buf);
    if(i == buf.len) {
        FIXME("The element is not in parent's child list?\n");
        return E_UNEXPECTED;
    }

    *ret = i;
    return S_OK;
}