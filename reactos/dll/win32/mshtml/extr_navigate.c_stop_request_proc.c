#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_6__ {TYPE_3__* bsc; } ;
typedef  TYPE_2__ stop_request_task_t ;
struct TYPE_5__ {int /*<<< orphan*/  entry; } ;
struct TYPE_7__ {TYPE_1__ bsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_stop_nsrequest (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_request_proc(task_t *_task)
{
    stop_request_task_t *task = (stop_request_task_t*)_task;

    TRACE("(%p)\n", task->bsc);

    list_remove(&task->bsc->bsc.entry);
    list_init(&task->bsc->bsc.entry);
    on_stop_nsrequest(task->bsc, S_OK);
}