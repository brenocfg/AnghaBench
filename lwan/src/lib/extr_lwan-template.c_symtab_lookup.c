#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct symtab {int /*<<< orphan*/  hash; struct symtab* next; } ;
struct parser {struct symtab* symtab; } ;
struct lwan_var_descriptor {int dummy; } ;

/* Variables and functions */
 struct lwan_var_descriptor* hash_find (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct lwan_var_descriptor *symtab_lookup(struct parser *parser,
                                                 const char *var_name)
{
    for (struct symtab *tab = parser->symtab; tab; tab = tab->next) {
        struct lwan_var_descriptor *var = hash_find(tab->hash, var_name);
        if (var)
            return var;
    }

    return NULL;
}