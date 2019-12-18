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
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMElementCSSInlineStyle ;
typedef  int /*<<< orphan*/  nsIDOMCSSStyleDeclaration ;
struct TYPE_3__ {int /*<<< orphan*/  nselem; } ;
typedef  TYPE_1__ HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IID_nsIDOMElementCSSInlineStyle ; 
 scalar_t__ NS_FAILED (scalar_t__) ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ nsIDOMElementCSSInlineStyle_GetStyle (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMElementCSSInlineStyle_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMHTMLElement_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static HRESULT get_style_from_elem(HTMLElement *elem, nsIDOMCSSStyleDeclaration **ret)
{
    nsIDOMElementCSSInlineStyle *nselemstyle;
    nsresult nsres;

    if(!elem->nselem) {
        FIXME("NULL nselem\n");
        return E_NOTIMPL;
    }

    nsres = nsIDOMHTMLElement_QueryInterface(elem->nselem, &IID_nsIDOMElementCSSInlineStyle,
            (void**)&nselemstyle);
    assert(nsres == NS_OK);

    nsres = nsIDOMElementCSSInlineStyle_GetStyle(nselemstyle, ret);
    nsIDOMElementCSSInlineStyle_Release(nselemstyle);
    if(NS_FAILED(nsres)) {
        ERR("GetStyle failed: %08x\n", nsres);
        return E_FAIL;
    }

    return S_OK;
}