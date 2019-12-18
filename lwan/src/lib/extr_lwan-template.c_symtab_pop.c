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
struct symtab {struct symtab* next; int /*<<< orphan*/  hash; } ;
struct parser {struct symtab* symtab; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct symtab*) ; 
 int /*<<< orphan*/  free (struct symtab*) ; 
 int /*<<< orphan*/  hash_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void symtab_pop(struct parser *parser)
{
    struct symtab *tab = parser->symtab;

    assert(tab);

    hash_free(tab->hash);
    parser->symtab = tab->next;
    free(tab);
}