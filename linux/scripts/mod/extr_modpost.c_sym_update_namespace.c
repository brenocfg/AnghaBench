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
struct symbol {int /*<<< orphan*/ * namespace; } ;

/* Variables and functions */
 int /*<<< orphan*/ * NOFAIL (int /*<<< orphan*/ ) ; 
 struct symbol* find_symbol (char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merror (char*,char const*,char const*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static void sym_update_namespace(const char *symname, const char *namespace)
{
	struct symbol *s = find_symbol(symname);

	/*
	 * That symbol should have been created earlier and thus this is
	 * actually an assertion.
	 */
	if (!s) {
		merror("Could not update namespace(%s) for symbol %s\n",
		       namespace, symname);
		return;
	}

	free(s->namespace);
	s->namespace =
		namespace && namespace[0] ? NOFAIL(strdup(namespace)) : NULL;
}