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
struct module {int is_dot_o; char* name; int gpl_compatible; struct module* next; } ;

/* Variables and functions */
 void* NOFAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (struct module*,int /*<<< orphan*/ ,int) ; 
 struct module* modules ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ strends (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static struct module *new_module(const char *modname)
{
	struct module *mod;
	char *p;

	mod = NOFAIL(malloc(sizeof(*mod)));
	memset(mod, 0, sizeof(*mod));
	p = NOFAIL(strdup(modname));

	/* strip trailing .o */
	if (strends(p, ".o")) {
		p[strlen(p) - 2] = '\0';
		mod->is_dot_o = 1;
	}

	/* add to list */
	mod->name = p;
	mod->gpl_compatible = -1;
	mod->next = modules;
	modules = mod;

	return mod;
}