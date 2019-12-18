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
typedef  int /*<<< orphan*/  nsIDOMNode ;
struct TYPE_5__ {int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  create_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static HRESULT HTMLDOMNode_clone(HTMLDOMNode *This, nsIDOMNode *nsnode, HTMLDOMNode **ret)
{
    return create_node(This->doc, nsnode, ret);
}