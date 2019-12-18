#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_header_t ;
struct TYPE_6__ {struct TYPE_6__* str; int /*<<< orphan*/  err; int /*<<< orphan*/  hres; } ;
typedef  TYPE_1__ report_result_task_t ;
struct TYPE_7__ {int /*<<< orphan*/  protocol_sink_handler; } ;
typedef  TYPE_2__ BindProtocol ;

/* Variables and functions */
 int /*<<< orphan*/  IInternetProtocolSink_ReportResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static void report_result_proc(BindProtocol *This, task_header_t *t)
{
    report_result_task_t *task = (report_result_task_t*)t;

    IInternetProtocolSink_ReportResult(This->protocol_sink_handler, task->hres, task->err, task->str);

    heap_free(task->str);
    heap_free(task);
}