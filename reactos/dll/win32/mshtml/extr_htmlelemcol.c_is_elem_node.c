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
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  scalar_t__ UINT16 ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ COMMENT_NODE ; 
 scalar_t__ ELEMENT_NODE ; 
 int /*<<< orphan*/  nsIDOMNode_GetNodeType (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static inline BOOL is_elem_node(nsIDOMNode *node)
{
    UINT16 type=0;

    nsIDOMNode_GetNodeType(node, &type);

    return type == ELEMENT_NODE || type == COMMENT_NODE;
}