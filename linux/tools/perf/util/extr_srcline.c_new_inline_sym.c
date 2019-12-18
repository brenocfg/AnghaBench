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
struct symbol {int inlined; int /*<<< orphan*/  type; int /*<<< orphan*/  binding; scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  name; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* dso__demangle_sym (struct dso*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct symbol* symbol__new (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct symbol *new_inline_sym(struct dso *dso,
				     struct symbol *base_sym,
				     const char *funcname)
{
	struct symbol *inline_sym;
	char *demangled = NULL;

	if (!funcname)
		funcname = "??";

	if (dso) {
		demangled = dso__demangle_sym(dso, 0, funcname);
		if (demangled)
			funcname = demangled;
	}

	if (base_sym && strcmp(funcname, base_sym->name) == 0) {
		/* reuse the real, existing symbol */
		inline_sym = base_sym;
		/* ensure that we don't alias an inlined symbol, which could
		 * lead to double frees in inline_node__delete
		 */
		assert(!base_sym->inlined);
	} else {
		/* create a fake symbol for the inline frame */
		inline_sym = symbol__new(base_sym ? base_sym->start : 0,
					 base_sym ? (base_sym->end - base_sym->start) : 0,
					 base_sym ? base_sym->binding : 0,
					 base_sym ? base_sym->type : 0,
					 funcname);
		if (inline_sym)
			inline_sym->inlined = 1;
	}

	free(demangled);

	return inline_sym;
}