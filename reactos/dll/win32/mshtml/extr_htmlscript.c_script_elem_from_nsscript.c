#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLScriptElement ;
struct TYPE_4__ {int /*<<< orphan*/ * vtbl; } ;
typedef  int /*<<< orphan*/  HTMLScriptElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  TYPE_1__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTMLScriptElementImplVtbl ; 
 int /*<<< orphan*/  IID_nsIDOMNode ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/ * impl_from_HTMLDOMNode (TYPE_1__*) ; 
 scalar_t__ nsIDOMHTMLScriptElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 

HRESULT script_elem_from_nsscript(HTMLDocumentNode *doc, nsIDOMHTMLScriptElement *nsscript, HTMLScriptElement **ret)
{
    nsIDOMNode *nsnode;
    HTMLDOMNode *node;
    nsresult nsres;
    HRESULT hres;

    nsres = nsIDOMHTMLScriptElement_QueryInterface(nsscript, &IID_nsIDOMNode, (void**)&nsnode);
    assert(nsres == NS_OK);

    hres = get_node(doc, nsnode, TRUE, &node);
    nsIDOMNode_Release(nsnode);
    if(FAILED(hres))
        return hres;

    assert(node->vtbl == &HTMLScriptElementImplVtbl);
    *ret = impl_from_HTMLDOMNode(node);
    return S_OK;
}