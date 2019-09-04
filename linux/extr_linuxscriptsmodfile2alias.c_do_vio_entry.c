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

/* Variables and functions */
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 char** compat ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 char** type ; 
 int /*<<< orphan*/  vio_device_id ; 

__attribute__((used)) static int do_vio_entry(const char *filename, void *symval,
		char *alias)
{
	char *tmp;
	DEF_FIELD_ADDR(symval, vio_device_id, type);
	DEF_FIELD_ADDR(symval, vio_device_id, compat);

	sprintf(alias, "vio:T%sS%s", (*type)[0] ? *type : "*",
			(*compat)[0] ? *compat : "*");

	/* Replace all whitespace with underscores */
	for (tmp = alias; tmp && *tmp; tmp++)
		if (isspace (*tmp))
			*tmp = '_';

	add_wildcard(alias);
	return 1;
}