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
struct module {int /*<<< orphan*/  dev_table_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 char** compatible ; 
 scalar_t__ isspace (char) ; 
 char** name ; 
 int /*<<< orphan*/  of_device_id ; 
 int sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char** type ; 

__attribute__((used)) static void do_of_entry_multi(void *symval, struct module *mod)
{
	char alias[500];
	int len;
	char *tmp;

	DEF_FIELD_ADDR(symval, of_device_id, name);
	DEF_FIELD_ADDR(symval, of_device_id, type);
	DEF_FIELD_ADDR(symval, of_device_id, compatible);

	len = sprintf(alias, "of:N%sT%s", (*name)[0] ? *name : "*",
		      (*type)[0] ? *type : "*");

	if ((*compatible)[0])
		sprintf(&alias[len], "%sC%s", (*type)[0] ? "*" : "",
			*compatible);

	/* Replace all whitespace with underscores */
	for (tmp = alias; tmp && *tmp; tmp++)
		if (isspace(*tmp))
			*tmp = '_';

	buf_printf(&mod->dev_table_buf, "MODULE_ALIAS(\"%s\");\n", alias);
	strcat(alias, "C");
	add_wildcard(alias);
	buf_printf(&mod->dev_table_buf, "MODULE_ALIAS(\"%s\");\n", alias);
}