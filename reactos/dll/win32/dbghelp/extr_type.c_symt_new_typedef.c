#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tag; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct symt_typedef {TYPE_1__ symt; TYPE_2__ hash_elt; struct symt* type; } ;
struct symt {int dummy; } ;
struct module {int /*<<< orphan*/  ht_types; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SymTagTypedef ; 
 int /*<<< orphan*/  hash_table_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 struct symt_typedef* pool_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pool_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  symt_add_type (struct module*,TYPE_1__*) ; 

struct symt_typedef* symt_new_typedef(struct module* module, struct symt* ref, 
                                      const char* name)
{
    struct symt_typedef* sym;

    if ((sym = pool_alloc(&module->pool, sizeof(*sym))))
    {
        sym->symt.tag = SymTagTypedef;
        sym->type     = ref;
        sym->hash_elt.name = pool_strdup(&module->pool, name);
        hash_table_add(&module->ht_types, &sym->hash_elt);
        symt_add_type(module, &sym->symt);
    }
    return sym;
}