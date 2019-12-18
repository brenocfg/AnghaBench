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
typedef  int uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  retval; } ;
typedef  TYPE_1__ njs_vm_t ;
typedef  int /*<<< orphan*/  njs_value_t ;
typedef  int /*<<< orphan*/  njs_uint_t ;
typedef  int /*<<< orphan*/  njs_int_t ;
typedef  int /*<<< orphan*/  njs_index_t ;
struct TYPE_8__ {scalar_t__ time; } ;
typedef  TYPE_2__ njs_console_t ;

/* Variables and functions */
 int /*<<< orphan*/  NJS_ERROR ; 
 int /*<<< orphan*/  NJS_OK ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  njs_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ njs_fast_path (int) ; 
 int /*<<< orphan*/  njs_printf (char*,...) ; 
 scalar_t__ njs_slow_path (int /*<<< orphan*/ ) ; 
 int njs_time () ; 
 int /*<<< orphan*/  njs_value_is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  njs_value_undefined ; 
 int /*<<< orphan*/  njs_vm_error (TYPE_1__*,char*) ; 
 TYPE_2__* njs_vm_external (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static njs_int_t
njs_ext_console_time_end(njs_vm_t *vm, njs_value_t *args, njs_uint_t nargs,
    njs_index_t unused)
{
    uint64_t       ns, ms;
    njs_console_t  *console;

    ns = njs_time();

    if (!njs_value_is_undefined(njs_arg(args, nargs, 1))) {
        njs_vm_error(vm, "labels not implemented");
        return NJS_ERROR;
    }

    console = njs_vm_external(vm, njs_arg(args, nargs, 0));
    if (njs_slow_path(console == NULL)) {
        return NJS_ERROR;
    }

    if (njs_fast_path(console->time != UINT64_MAX)) {

        ns = ns - console->time;

        ms = ns / 1000000;
        ns = ns % 1000000;

        njs_printf("default: %uL.%06uLms\n", ms, ns);

        console->time = UINT64_MAX;

    } else {
        njs_printf("Timer \"default\" doesn’t exist.\n");
    }

    vm->retval = njs_value_undefined;

    return NJS_OK;
}