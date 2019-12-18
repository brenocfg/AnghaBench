#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMEventTarget ;
struct TYPE_15__ {int /*<<< orphan*/  nsIDOMEventListener_iface; } ;
struct TYPE_13__ {int ref; TYPE_6__ load_listener; TYPE_6__ keypress_listener; TYPE_6__ focus_listener; TYPE_6__ blur_listener; TYPE_6__ htmlevent_listener; TYPE_4__* doc; } ;
typedef  TYPE_3__ nsDocumentEventListener ;
struct TYPE_12__ {TYPE_1__* window; } ;
struct TYPE_14__ {TYPE_2__ basedoc; TYPE_3__* nsevent_listener; } ;
struct TYPE_11__ {int /*<<< orphan*/  nswindow; } ;
typedef  TYPE_4__ HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_nsIDOMEventTarget ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  blurW ; 
 int /*<<< orphan*/  blur_vtbl ; 
 int /*<<< orphan*/  focusW ; 
 int /*<<< orphan*/  focus_vtbl ; 
 TYPE_3__* heap_alloc (int) ; 
 int /*<<< orphan*/  htmlevent_vtbl ; 
 int /*<<< orphan*/  init_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_listener (TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keypressW ; 
 int /*<<< orphan*/  keypress_vtbl ; 
 int /*<<< orphan*/  loadW ; 
 int /*<<< orphan*/  load_vtbl ; 
 int /*<<< orphan*/  nsIDOMEventTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMWindow_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

void init_nsevents(HTMLDocumentNode *doc)
{
    nsDocumentEventListener *listener;
    nsIDOMEventTarget *target;
    nsresult nsres;

    listener = heap_alloc(sizeof(nsDocumentEventListener));
    if(!listener)
        return;

    TRACE("%p %p\n", doc, listener);

    listener->ref = 1;
    listener->doc = doc;

    init_listener(&listener->blur_listener,        listener, &blur_vtbl);
    init_listener(&listener->focus_listener,       listener, &focus_vtbl);
    init_listener(&listener->keypress_listener,    listener, &keypress_vtbl);
    init_listener(&listener->load_listener,        listener, &load_vtbl);
    init_listener(&listener->htmlevent_listener,   listener, &htmlevent_vtbl);

    doc->nsevent_listener = listener;

    nsres = nsIDOMWindow_QueryInterface(doc->basedoc.window->nswindow, &IID_nsIDOMEventTarget, (void**)&target);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDOMEventTarget interface: %08x\n", nsres);
        return;
    }

    init_event(target, blurW,     &listener->blur_listener.nsIDOMEventListener_iface,     TRUE);
    init_event(target, focusW,    &listener->focus_listener.nsIDOMEventListener_iface,    TRUE);
    init_event(target, keypressW, &listener->keypress_listener.nsIDOMEventListener_iface, FALSE);
    init_event(target, loadW,     &listener->load_listener.nsIDOMEventListener_iface,     TRUE);

    nsIDOMEventTarget_Release(target);
}