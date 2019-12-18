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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMWindow ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsIDOMDocument ;
struct TYPE_4__ {int /*<<< orphan*/ * inner_window; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  TYPE_2__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HTMLInnerWindow ;

/* Variables and functions */
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDOMDocument_GetDefaultView (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_GetOwnerDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMWindow_Release (int /*<<< orphan*/ *) ; 
 TYPE_2__* nswindow_to_window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HTMLInnerWindow *get_elem_window(nsIDOMHTMLElement *elem)
{
    nsIDOMWindow *nswindow;
    nsIDOMDocument *nsdoc;
    HTMLOuterWindow *window;
    nsresult nsres;

    nsres = nsIDOMHTMLElement_GetOwnerDocument(elem, &nsdoc);
    if(NS_FAILED(nsres))
        return NULL;

    nsres = nsIDOMDocument_GetDefaultView(nsdoc, &nswindow);
    nsIDOMDocument_Release(nsdoc);
    if(NS_FAILED(nsres) || !nswindow)
        return NULL;

    window = nswindow_to_window(nswindow);
    nsIDOMWindow_Release(nswindow);

    return window->base.inner_window;
}