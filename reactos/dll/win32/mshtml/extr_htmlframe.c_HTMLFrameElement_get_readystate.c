#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  IHTMLFrameBase2_iface; } ;
struct TYPE_5__ {TYPE_1__ framebase; } ;
typedef  TYPE_2__ HTMLFrameElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLFrameBase2_get_readyState (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLFrameElement_get_readystate(HTMLDOMNode *iface, BSTR *p)
{
    HTMLFrameElement *This = impl_from_HTMLDOMNode(iface);

    return IHTMLFrameBase2_get_readyState(&This->framebase.IHTMLFrameBase2_iface, p);
}