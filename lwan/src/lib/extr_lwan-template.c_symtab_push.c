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
struct lwan_var_descriptor {scalar_t__ name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int errno ; 
 int /*<<< orphan*/  free (struct symtab*) ; 
 int hash_add (int /*<<< orphan*/ ,scalar_t__,struct lwan_var_descriptor const*) ; 
 int /*<<< orphan*/  hash_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_str_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct symtab* malloc (int) ; 

__attribute__((used)) static int symtab_push(struct parser *parser,
                       const struct lwan_var_descriptor *descriptor)
{
    struct symtab *tab;
    int r;

    if (!descriptor)
        return -ENODEV;

    tab = malloc(sizeof(*tab));
    if (!tab)
        return -errno;

    tab->hash = hash_str_new(NULL, NULL);
    if (!tab->hash) {
        r = -ENOMEM;
        goto hash_new_err;
    }

    tab->next = parser->symtab;
    parser->symtab = tab;

    for (; descriptor->name; descriptor++) {
        r = hash_add(parser->symtab->hash, descriptor->name, descriptor);

        if (r < 0)
            goto hash_add_err;
    }

    return 0;

hash_add_err:
    hash_free(tab->hash);
hash_new_err:
    free(tab);

    return r;
}