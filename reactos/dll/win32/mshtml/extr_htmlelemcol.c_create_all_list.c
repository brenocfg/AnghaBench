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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  elem_vector_t ;
typedef  scalar_t__ UINT32 ;
struct TYPE_5__ {int /*<<< orphan*/  nsnode; } ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  TYPE_1__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  elem_from_HTMLDOMNode (TYPE_1__*) ; 
 int /*<<< orphan*/  elem_vector_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ is_elem_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNodeList_GetLength (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Item (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_GetChildNodes (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void create_all_list(HTMLDocumentNode *doc, HTMLDOMNode *elem, elem_vector_t *buf)
{
    nsIDOMNodeList *nsnode_list;
    nsIDOMNode *iter;
    UINT32 list_len = 0, i;
    nsresult nsres;
    HRESULT hres;

    nsres = nsIDOMNode_GetChildNodes(elem->nsnode, &nsnode_list);
    if(NS_FAILED(nsres)) {
        ERR("GetChildNodes failed: %08x\n", nsres);
        return;
    }

    nsIDOMNodeList_GetLength(nsnode_list, &list_len);
    if(!list_len)
        return;

    for(i=0; i<list_len; i++) {
        nsres = nsIDOMNodeList_Item(nsnode_list, i, &iter);
        if(NS_FAILED(nsres)) {
            ERR("Item failed: %08x\n", nsres);
            continue;
        }

        if(is_elem_node(iter)) {
            HTMLDOMNode *node;

            hres = get_node(doc, iter, TRUE, &node);
            if(FAILED(hres)) {
                FIXME("get_node failed: %08x\n", hres);
                continue;
            }

            elem_vector_add(buf, elem_from_HTMLDOMNode(node));
            create_all_list(doc, node, buf);
        }
    }
}