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
struct symt_array {int start; int end; TYPE_1__ symt; struct symt* index_type; struct symt* base_type; } ;
struct symt {int dummy; } ;
struct module {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SymTagArrayType ; 
 struct symt_array* pool_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  symt_add_type (struct module*,TYPE_1__*) ; 

struct symt_array* symt_new_array(struct module* module, int min, int max, 
                                  struct symt* base, struct symt* index)
{
    struct symt_array*  sym;

    if ((sym = pool_alloc(&module->pool, sizeof(*sym))))
    {
        sym->symt.tag   = SymTagArrayType;
        sym->start      = min;
        sym->end        = max;
        sym->base_type  = base;
        sym->index_type = index;
        symt_add_type(module, &sym->symt);
    }
    return sym;
}