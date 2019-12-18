#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tag; } ;
struct symt_function_signature {int /*<<< orphan*/  vchildren; TYPE_1__ symt; } ;
struct symt {int /*<<< orphan*/  tag; } ;
struct symt_function_arg_type {struct symt symt; TYPE_1__* container; struct symt* arg_type; } ;
struct module {int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SymTagFunctionArgType ; 
 scalar_t__ SymTagFunctionType ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 struct symt_function_arg_type* pool_alloc (int /*<<< orphan*/ *,int) ; 
 struct symt** vector_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL symt_add_function_signature_parameter(struct module* module,
                                           struct symt_function_signature* sig_type,
                                           struct symt* param)
{
    struct symt**                       p;
    struct symt_function_arg_type*      arg;

    assert(sig_type->symt.tag == SymTagFunctionType);
    arg = pool_alloc(&module->pool, sizeof(*arg));
    if (!arg) return FALSE;
    arg->symt.tag = SymTagFunctionArgType;
    arg->arg_type = param;
    arg->container = &sig_type->symt;
    p = vector_add(&sig_type->vchildren, &module->pool);
    if (!p) return FALSE; /* FIXME we leak arg */
    *p = &arg->symt;

    return TRUE;
}