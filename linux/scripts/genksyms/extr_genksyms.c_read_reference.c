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
struct symbol {int is_override; } ;
struct string_list {scalar_t__ tag; int /*<<< orphan*/  string; struct string_list* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ SYM_NORMAL ; 
 struct symbol* add_reference_symbol (int /*<<< orphan*/ ,scalar_t__,struct string_list*,int) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_node (struct string_list*) ; 
 struct string_list* read_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_reference(FILE *f)
{
	while (!feof(f)) {
		struct string_list *defn = NULL;
		struct string_list *sym, *def;
		int is_extern = 0, is_override = 0;
		struct symbol *subsym;

		sym = read_node(f);
		if (sym && sym->tag == SYM_NORMAL &&
		    !strcmp(sym->string, "override")) {
			is_override = 1;
			free_node(sym);
			sym = read_node(f);
		}
		if (!sym)
			continue;
		def = read_node(f);
		if (def && def->tag == SYM_NORMAL &&
		    !strcmp(def->string, "extern")) {
			is_extern = 1;
			free_node(def);
			def = read_node(f);
		}
		while (def) {
			def->next = defn;
			defn = def;
			def = read_node(f);
		}
		subsym = add_reference_symbol(xstrdup(sym->string), sym->tag,
					      defn, is_extern);
		subsym->is_override = is_override;
		free_node(sym);
	}
}