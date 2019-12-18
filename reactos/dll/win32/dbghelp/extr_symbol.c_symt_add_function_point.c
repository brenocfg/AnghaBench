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
struct symt {int tag; } ;
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;
struct location {int dummy; } ;
struct symt_hierarchy_point {struct symt symt; TYPE_1__ hash_elt; struct location loc; int /*<<< orphan*/ * parent; } ;
struct symt_function {int /*<<< orphan*/  vchildren; int /*<<< orphan*/  symt; } ;
struct module {int /*<<< orphan*/  pool; } ;
typedef  enum SymTagEnum { ____Placeholder_SymTagEnum } SymTagEnum ;

/* Variables and functions */
 struct symt_hierarchy_point* pool_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pool_strdup (int /*<<< orphan*/ *,char const*) ; 
 struct symt** vector_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct symt_hierarchy_point* symt_add_function_point(struct module* module,
                                                     struct symt_function* func,
                                                     enum SymTagEnum point,
                                                     const struct location* loc,
                                                     const char* name)
{
    struct symt_hierarchy_point*sym;
    struct symt**               p;

    if ((sym = pool_alloc(&module->pool, sizeof(*sym))))
    {
        sym->symt.tag = point;
        sym->parent   = &func->symt;
        sym->loc      = *loc;
        sym->hash_elt.name = name ? pool_strdup(&module->pool, name) : NULL;
        p = vector_add(&func->vchildren, &module->pool);
        *p = &sym->symt;
    }
    return sym;
}