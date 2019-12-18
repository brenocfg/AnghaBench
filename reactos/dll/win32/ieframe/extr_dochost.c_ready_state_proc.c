#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_header_t ;
struct TYPE_5__ {scalar_t__ doc; int /*<<< orphan*/  ready_state; } ;
typedef  TYPE_1__ ready_state_task_t ;
struct TYPE_6__ {scalar_t__ document; } ;
typedef  TYPE_2__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  update_ready_state (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ready_state_proc(DocHost *This, task_header_t *_task)
{
    ready_state_task_t *task = (ready_state_task_t*)_task;

    if(task->doc == This->document)
        update_ready_state(This, task->ready_state);
}