#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_4__* inner_window; } ;
struct TYPE_21__ {TYPE_8__* frame_element; TYPE_5__ base; TYPE_2__* doc_obj; int /*<<< orphan*/  readystate_pending; } ;
struct TYPE_18__ {int /*<<< orphan*/  nsnode; TYPE_11__* doc; } ;
struct TYPE_19__ {TYPE_6__ node; } ;
struct TYPE_20__ {TYPE_7__ element; } ;
struct TYPE_16__ {TYPE_11__* doc; } ;
struct TYPE_15__ {int /*<<< orphan*/  nsnode; } ;
struct TYPE_13__ {int /*<<< orphan*/  cp_container; TYPE_9__* window; } ;
struct TYPE_14__ {TYPE_1__ basedoc; } ;
struct TYPE_12__ {TYPE_3__ node; } ;
typedef  TYPE_9__ HTMLOuterWindow ;

/* Variables and functions */
 int /*<<< orphan*/  DISPID_READYSTATE ; 
 int /*<<< orphan*/  EVENTID_READYSTATECHANGE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  call_property_onchanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fire_event (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void notif_readystate(HTMLOuterWindow *window)
{
    window->readystate_pending = FALSE;

    if(window->doc_obj && window->doc_obj->basedoc.window == window)
        call_property_onchanged(&window->doc_obj->basedoc.cp_container, DISPID_READYSTATE);

    fire_event(window->base.inner_window->doc, EVENTID_READYSTATECHANGE, FALSE,
            window->base.inner_window->doc->node.nsnode, NULL, NULL);

    if(window->frame_element)
        fire_event(window->frame_element->element.node.doc, EVENTID_READYSTATECHANGE,
                   TRUE, window->frame_element->element.node.nsnode, NULL, NULL);
}