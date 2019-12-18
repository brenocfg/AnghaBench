#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  IHTMLWindow2_iface; TYPE_7__* outer_window; } ;
struct TYPE_21__ {TYPE_6__ base; int /*<<< orphan*/  task_magic; TYPE_11__* doc; } ;
struct TYPE_18__ {TYPE_8__* inner_window; } ;
struct TYPE_20__ {TYPE_5__ base; TYPE_2__* doc_obj; } ;
struct TYPE_16__ {int /*<<< orphan*/ * forward_container; } ;
struct TYPE_17__ {TYPE_3__ cp_container; } ;
struct TYPE_14__ {TYPE_7__* window; } ;
struct TYPE_15__ {TYPE_1__ basedoc; } ;
struct TYPE_13__ {int /*<<< orphan*/  plugin_hosts; TYPE_4__ basedoc; } ;
typedef  TYPE_7__ HTMLOuterWindow ;
typedef  TYPE_8__ HTMLInnerWindow ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PluginHost ; 
 int /*<<< orphan*/  abort_window_bindings (TYPE_8__*) ; 
 int /*<<< orphan*/  detach_events (TYPE_11__*) ; 
 int /*<<< orphan*/  detach_plugin_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_script_hosts (TYPE_8__*) ; 
 int /*<<< orphan*/  remove_target_tasks (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void detach_inner_window(HTMLInnerWindow *window)
{
    HTMLOuterWindow *outer_window = window->base.outer_window;

    if(outer_window && outer_window->doc_obj && outer_window == outer_window->doc_obj->basedoc.window)
        window->doc->basedoc.cp_container.forward_container = NULL;

    if(window->doc) {
        detach_events(window->doc);
        while(!list_empty(&window->doc->plugin_hosts))
            detach_plugin_host(LIST_ENTRY(list_head(&window->doc->plugin_hosts), PluginHost, entry));
    }

    abort_window_bindings(window);
    remove_target_tasks(window->task_magic);
    release_script_hosts(window);
    window->base.outer_window = NULL;

    if(outer_window && outer_window->base.inner_window == window) {
        outer_window->base.inner_window = NULL;
        IHTMLWindow2_Release(&window->base.IHTMLWindow2_iface);
    }
}