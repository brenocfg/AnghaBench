#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  IHTMLImgElement_iface; } ;
typedef  TYPE_1__ HTMLImgElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLImgElement_get_readyState (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLImgElement_get_readystate(HTMLDOMNode *iface, BSTR *p)
{
    HTMLImgElement *This = impl_from_HTMLDOMNode(iface);

    return IHTMLImgElement_get_readyState(&This->IHTMLImgElement_iface, p);
}