#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  njs_vm_t ;
struct TYPE_9__ {int length; int /*<<< orphan*/ * start; } ;
typedef  TYPE_1__ njs_str_t ;
struct TYPE_10__ {scalar_t__ disassemble; } ;
typedef  TYPE_2__ njs_opts_t ;
typedef  scalar_t__ njs_int_t ;
struct TYPE_11__ {int /*<<< orphan*/ * vm; } ;
typedef  TYPE_3__ njs_console_t ;

/* Variables and functions */
 scalar_t__ NJS_ERROR ; 
 scalar_t__ NJS_OK ; 
 int /*<<< orphan*/  njs_disassembler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  njs_printf (char*) ; 
 scalar_t__ njs_process_events (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ njs_slow_path (int) ; 
 int /*<<< orphan*/  njs_stderror (char*) ; 
 scalar_t__ njs_vm_compile (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  njs_vm_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  njs_vm_posted (int /*<<< orphan*/ *) ; 
 scalar_t__ njs_vm_run (int /*<<< orphan*/ *) ; 
 scalar_t__ njs_vm_start (int /*<<< orphan*/ *) ; 
 scalar_t__ njs_vm_waiting (int /*<<< orphan*/ *) ; 

__attribute__((used)) static njs_int_t
njs_process_script(njs_console_t *console, njs_opts_t *opts,
    const njs_str_t *script)
{
    u_char     *start;
    njs_vm_t   *vm;
    njs_int_t  ret;

    vm = console->vm;
    start = script->start;

    ret = njs_vm_compile(vm, &start, start + script->length);

    if (ret == NJS_OK) {
        if (opts->disassemble) {
            njs_disassembler(vm);
            njs_printf("\n");
        }

        ret = njs_vm_start(vm);
    }

    for ( ;; ) {
        if (!njs_vm_pending(vm)) {
            break;
        }

        ret = njs_process_events(console, opts);
        if (njs_slow_path(ret != NJS_OK)) {
            njs_stderror("njs_process_events() failed\n");
            ret = NJS_ERROR;
            break;
        }

        if (njs_vm_waiting(vm) && !njs_vm_posted(vm)) {
            /*TODO: async events. */

            njs_stderror("njs_process_script(): async events unsupported\n");
            ret = NJS_ERROR;
            break;
        }

        ret = njs_vm_run(vm);
    }

    return ret;
}