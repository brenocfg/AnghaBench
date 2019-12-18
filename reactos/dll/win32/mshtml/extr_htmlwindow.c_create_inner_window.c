#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  IHTMLWindow2_iface; TYPE_3__* inner_window; int /*<<< orphan*/ * outer_window; } ;
struct TYPE_6__ {int /*<<< orphan*/  dispex; } ;
struct TYPE_8__ {int /*<<< orphan*/ * mon; int /*<<< orphan*/  task_magic; TYPE_2__ base; TYPE_1__ event_target; int /*<<< orphan*/  script_queue; int /*<<< orphan*/  bindings; int /*<<< orphan*/  script_hosts; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  HTMLOuterWindow ;
typedef  TYPE_3__ HTMLInnerWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLWindow_dispex ; 
 int /*<<< orphan*/  IMoniker_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* alloc_window (int) ; 
 int /*<<< orphan*/  get_task_target_magic () ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_inner_window(HTMLOuterWindow *outer_window, IMoniker *mon, HTMLInnerWindow **ret)
{
    HTMLInnerWindow *window;

    window = alloc_window(sizeof(HTMLInnerWindow));
    if(!window)
        return E_OUTOFMEMORY;

    list_init(&window->script_hosts);
    list_init(&window->bindings);
    list_init(&window->script_queue);

    window->base.outer_window = outer_window;
    window->base.inner_window = window;

    init_dispex(&window->event_target.dispex, (IUnknown*)&window->base.IHTMLWindow2_iface, &HTMLWindow_dispex);

    window->task_magic = get_task_target_magic();

    if(mon) {
        IMoniker_AddRef(mon);
        window->mon = mon;
    }

    *ret = window;
    return S_OK;
}