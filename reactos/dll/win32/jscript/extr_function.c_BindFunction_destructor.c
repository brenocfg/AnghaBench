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
struct TYPE_5__ {unsigned int argc; int /*<<< orphan*/  this; TYPE_1__* target; int /*<<< orphan*/ * args; } ;
struct TYPE_4__ {int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  FunctionInstance ;
typedef  TYPE_2__ BindFunction ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void BindFunction_destructor(FunctionInstance *func)
{
    BindFunction *function = (BindFunction*)func;
    unsigned i;

    TRACE("%p\n", function);

    for(i = 0; i < function->argc; i++)
        jsval_release(function->args[i]);
    jsdisp_release(&function->target->dispex);
    IDispatch_Release(function->this);
}