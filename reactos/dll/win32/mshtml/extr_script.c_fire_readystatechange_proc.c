#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_8__ {TYPE_3__* elem; } ;
typedef  TYPE_4__ fire_readystatechange_task_t ;
struct TYPE_6__ {int /*<<< orphan*/  nsnode; int /*<<< orphan*/  doc; } ;
struct TYPE_5__ {TYPE_2__ node; } ;
struct TYPE_7__ {TYPE_1__ element; scalar_t__ pending_readystatechange_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTID_READYSTATECHANGE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  fire_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fire_readystatechange_proc(task_t *_task)
{
    fire_readystatechange_task_t *task = (fire_readystatechange_task_t*)_task;

    if(!task->elem->pending_readystatechange_event)
        return;

    task->elem->pending_readystatechange_event = FALSE;
    fire_event(task->elem->element.node.doc, EVENTID_READYSTATECHANGE, FALSE, task->elem->element.node.nsnode, NULL, NULL);
}