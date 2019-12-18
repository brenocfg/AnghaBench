#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_7__ {TYPE_4__* bscallback; TYPE_3__* window; int /*<<< orphan*/  uri; int /*<<< orphan*/  flags; int /*<<< orphan*/  mon; } ;
typedef  TYPE_1__ navigate_task_t ;
struct TYPE_8__ {int /*<<< orphan*/  mon; } ;
struct TYPE_10__ {TYPE_2__ bsc; } ;
struct TYPE_9__ {int /*<<< orphan*/  pending_window; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  set_current_mon (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_uri (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_moniker (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_binding (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void navigate_proc(task_t *_task)
{
    navigate_task_t *task = (navigate_task_t*)_task;
    HRESULT hres;

    hres = set_moniker(task->window, task->mon, task->uri, NULL, task->bscallback, TRUE);
    if(SUCCEEDED(hres)) {
        set_current_mon(task->window, task->bscallback->bsc.mon, task->flags);
        set_current_uri(task->window, task->uri);
        start_binding(task->window->pending_window, &task->bscallback->bsc, NULL);
    }
}