#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  njs_vm_t ;
typedef  int /*<<< orphan*/  njs_int_t ;
struct TYPE_4__ {int /*<<< orphan*/ * completions; } ;
struct TYPE_5__ {TYPE_1__ completion; int /*<<< orphan*/  time; int /*<<< orphan*/  posted_events; int /*<<< orphan*/  events; int /*<<< orphan*/ * vm; } ;
typedef  TYPE_2__ njs_console_t ;

/* Variables and functions */
 int /*<<< orphan*/  NJS_ERROR ; 
 int /*<<< orphan*/  NJS_OK ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  njs_lvlhsh_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  njs_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * njs_vm_completions (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static njs_int_t
njs_console_init(njs_vm_t *vm, njs_console_t *console)
{
    console->vm = vm;

    njs_lvlhsh_init(&console->events);
    njs_queue_init(&console->posted_events);

    console->time = UINT64_MAX;

    console->completion.completions = njs_vm_completions(vm, NULL);
    if (console->completion.completions == NULL) {
        return NJS_ERROR;
    }

    return NJS_OK;
}