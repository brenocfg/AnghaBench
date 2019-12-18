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
struct TYPE_7__ {int /*<<< orphan*/  retval; } ;
typedef  TYPE_1__ njs_vm_t ;
typedef  int /*<<< orphan*/  njs_value_t ;
typedef  int /*<<< orphan*/  njs_uint_t ;
typedef  int /*<<< orphan*/  njs_int_t ;
typedef  int /*<<< orphan*/  njs_index_t ;
struct TYPE_8__ {int /*<<< orphan*/  time; } ;
typedef  TYPE_2__ njs_console_t ;

/* Variables and functions */
 int /*<<< orphan*/  NJS_ERROR ; 
 int /*<<< orphan*/  NJS_OK ; 
 int /*<<< orphan*/  njs_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ njs_slow_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  njs_time () ; 
 int /*<<< orphan*/  njs_value_is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  njs_value_undefined ; 
 int /*<<< orphan*/  njs_vm_error (TYPE_1__*,char*) ; 
 TYPE_2__* njs_vm_external (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static njs_int_t
njs_ext_console_time(njs_vm_t *vm, njs_value_t *args, njs_uint_t nargs,
    njs_index_t unused)
{
    njs_console_t  *console;

    if (!njs_value_is_undefined(njs_arg(args, nargs, 1))) {
        njs_vm_error(vm, "labels not implemented");
        return NJS_ERROR;
    }

    console = njs_vm_external(vm, njs_arg(args, nargs, 0));
    if (njs_slow_path(console == NULL)) {
        return NJS_ERROR;
    }

    console->time = njs_time();

    vm->retval = njs_value_undefined;

    return NJS_OK;
}