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
 int /*<<< orphan*/  Assert (char**) ; 
 char* pnstrdup (char const*,int) ; 
 char* pstrdup (char const*) ; 
 char* rindex (char const*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

void
llvm_split_symbol_name(const char *name, char **modname, char **funcname)
{
	*modname = NULL;
	*funcname = NULL;

	/*
	 * Module function names are pgextern.$module.$funcname
	 */
	if (strncmp(name, "pgextern.", strlen("pgextern.")) == 0)
	{
		/*
		 * Symbol names cannot contain a ., therefore we can split based on
		 * first and last occurrence of one.
		 */
		*funcname = rindex(name, '.');
		(*funcname)++;			/* jump over . */

		*modname = pnstrdup(name + strlen("pgextern."),
							*funcname - name - strlen("pgextern.") - 1);
		Assert(funcname);

		*funcname = pstrdup(*funcname);
	}
	else
	{
		*modname = NULL;
		*funcname = pstrdup(name);
	}
}