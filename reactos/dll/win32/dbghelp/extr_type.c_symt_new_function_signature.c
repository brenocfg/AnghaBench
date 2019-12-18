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
struct TYPE_2__ {int /*<<< orphan*/  tag; } ;
struct symt_function_signature {int call_conv; TYPE_1__ symt; int /*<<< orphan*/  vchildren; struct symt* rettype; } ;
struct symt {int dummy; } ;
struct module {int /*<<< orphan*/  pool; } ;
typedef  enum CV_call_e { ____Placeholder_CV_call_e } CV_call_e ;

/* Variables and functions */
 int /*<<< orphan*/  SymTagFunctionType ; 
 struct symt_function_signature* pool_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  symt_add_type (struct module*,TYPE_1__*) ; 
 int /*<<< orphan*/  vector_init (int /*<<< orphan*/ *,int,int) ; 

struct symt_function_signature* symt_new_function_signature(struct module* module, 
                                                            struct symt* ret_type,
                                                            enum CV_call_e call_conv)
{
    struct symt_function_signature*     sym;

    if ((sym = pool_alloc(&module->pool, sizeof(*sym))))
    {
        sym->symt.tag = SymTagFunctionType;
        sym->rettype  = ret_type;
        vector_init(&sym->vchildren, sizeof(struct symt*), 4);
        sym->call_conv = call_conv;
        symt_add_type(module, &sym->symt);
    }
    return sym;
}