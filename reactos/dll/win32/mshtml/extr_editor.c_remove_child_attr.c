#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  cpp_bool ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ELEMENT_NODE ; 
 int /*<<< orphan*/  IID_nsIDOMElement ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMElement_GetChildNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMElement_GetTagName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMElement_HasChildNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMElement_RemoveAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNodeList_GetLength (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Item (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_GetNodeType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_child_attr(nsIDOMElement *elem, LPCWSTR tag, nsAString *attr_str)
{
    cpp_bool has_children;
    UINT32 child_cnt, i;
    nsIDOMNode *child_node;
    nsIDOMNodeList *node_list;
    UINT16 node_type;

    nsIDOMElement_HasChildNodes(elem, &has_children);
    if(!has_children)
        return;

    nsIDOMElement_GetChildNodes(elem, &node_list);
    nsIDOMNodeList_GetLength(node_list, &child_cnt);

    for(i=0; i<child_cnt; i++) {
        nsIDOMNodeList_Item(node_list, i, &child_node);

        nsIDOMNode_GetNodeType(child_node, &node_type);
        if(node_type == ELEMENT_NODE) {
            nsIDOMElement *child_elem;
            nsAString tag_str;
            const PRUnichar *ctag;

            nsIDOMNode_QueryInterface(child_node, &IID_nsIDOMElement, (void**)&child_elem);

            nsAString_Init(&tag_str, NULL);
            nsIDOMElement_GetTagName(child_elem, &tag_str);
            nsAString_GetData(&tag_str, &ctag);

            if(!strcmpiW(ctag, tag))
                /* FIXME: remove node if there are no more attributes */
                nsIDOMElement_RemoveAttribute(child_elem, attr_str);

            nsAString_Finish(&tag_str);

            remove_child_attr(child_elem, tag, attr_str);

            nsIDOMElement_Release(child_elem);
        }

        nsIDOMNode_Release(child_node);
    }

    nsIDOMNodeList_Release(node_list);
}