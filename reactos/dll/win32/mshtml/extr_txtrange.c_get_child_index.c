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
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
typedef  int /*<<< orphan*/  nsIDOMNode ;

/* Variables and functions */
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ nsIDOMNodeList_Item (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMNode_GetChildNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_child_index(nsIDOMNode *parent, nsIDOMNode *child)
{
    nsIDOMNodeList *node_list;
    nsIDOMNode *node;
    int ret = 0;
    nsresult nsres;

    nsres = nsIDOMNode_GetChildNodes(parent, &node_list);
    assert(nsres == NS_OK);

    while(1) {
        nsres = nsIDOMNodeList_Item(node_list, ret, &node);
        assert(nsres == NS_OK && node);
        if(node == child) {
            nsIDOMNode_Release(node);
            break;
        }
        nsIDOMNode_Release(node);
        ret++;
    }

    nsIDOMNodeList_Release(node_list);
    return ret;
}