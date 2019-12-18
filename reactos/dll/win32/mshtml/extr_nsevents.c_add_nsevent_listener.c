#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMEventTarget ;
struct TYPE_10__ {TYPE_3__* window; } ;
struct TYPE_11__ {TYPE_2__* nsevent_listener; TYPE_4__ basedoc; } ;
struct TYPE_9__ {int /*<<< orphan*/  nswindow; } ;
struct TYPE_7__ {int /*<<< orphan*/  nsIDOMEventListener_iface; } ;
struct TYPE_8__ {TYPE_1__ htmlevent_listener; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_5__ HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIDOMEventTarget ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  init_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDOMEventTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMWindow_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

void add_nsevent_listener(HTMLDocumentNode *doc, nsIDOMNode *nsnode, LPCWSTR type)
{
    nsIDOMEventTarget *target;
    nsresult nsres;

    if(nsnode)
        nsres = nsIDOMNode_QueryInterface(nsnode, &IID_nsIDOMEventTarget, (void**)&target);
    else
        nsres = nsIDOMWindow_QueryInterface(doc->basedoc.window->nswindow, &IID_nsIDOMEventTarget, (void**)&target);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDOMEventTarget interface: %08x\n", nsres);
        return;
    }

    init_event(target, type, &doc->nsevent_listener->htmlevent_listener.nsIDOMEventListener_iface,
            TRUE);
    nsIDOMEventTarget_Release(target);
}