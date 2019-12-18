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
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  nsIDOMNodeList_Item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_GetChildNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static nsIDOMNode *get_child_node(nsIDOMNode *node, UINT32 off)
{
    nsIDOMNodeList *node_list;
    nsIDOMNode *ret = NULL;

    nsIDOMNode_GetChildNodes(node, &node_list);
    nsIDOMNodeList_Item(node_list, off, &ret);
    nsIDOMNodeList_Release(node_list);

    return ret;
}