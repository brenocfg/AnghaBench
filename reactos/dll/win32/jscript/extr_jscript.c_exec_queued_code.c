#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_1__ bytecode_t ;
struct TYPE_8__ {TYPE_1__* queue_head; } ;
typedef  TYPE_2__ JScript ;

/* Variables and functions */
 int /*<<< orphan*/  clear_script_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  exec_global_code (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void exec_queued_code(JScript *This)
{
    bytecode_t *iter;

    for(iter = This->queue_head; iter; iter = iter->next)
        exec_global_code(This, iter);

    clear_script_queue(This);
}