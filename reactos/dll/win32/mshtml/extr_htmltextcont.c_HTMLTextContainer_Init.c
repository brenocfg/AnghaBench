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
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  dispex_static_data_t ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  element; TYPE_1__ IHTMLTextContainer_iface; } ;
typedef  TYPE_2__ HTMLTextContainer ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLElement_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLTextContainerVtbl ; 

void HTMLTextContainer_Init(HTMLTextContainer *This, HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem,
        dispex_static_data_t *dispex_data)
{
    This->IHTMLTextContainer_iface.lpVtbl = &HTMLTextContainerVtbl;

    HTMLElement_Init(&This->element, doc, nselem, dispex_data);
}