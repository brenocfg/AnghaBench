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
typedef  int /*<<< orphan*/  wstrbuf_t ;
typedef  int /*<<< orphan*/  nsIDOMNode ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  nsIDOMNode_GetFirstChild (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_GetNextSibling (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wstrbuf_append_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wstrbuf_append_node_rec(wstrbuf_t *buf, nsIDOMNode *node)
{
    nsIDOMNode *iter, *tmp;

    wstrbuf_append_node(buf, node, FALSE);

    nsIDOMNode_GetFirstChild(node, &iter);
    while(iter) {
        wstrbuf_append_node_rec(buf, iter);
        nsIDOMNode_GetNextSibling(iter, &tmp);
        nsIDOMNode_Release(iter);
        iter = tmp;
    }
}