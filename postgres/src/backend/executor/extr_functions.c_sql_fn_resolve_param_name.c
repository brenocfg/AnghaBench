#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nargs; scalar_t__* argnames; } ;
typedef  TYPE_1__* SQLFunctionParseInfoPtr ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * sql_fn_make_param (TYPE_1__*,int,int) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static Node *
sql_fn_resolve_param_name(SQLFunctionParseInfoPtr pinfo,
						  const char *paramname, int location)
{
	int			i;

	if (pinfo->argnames == NULL)
		return NULL;

	for (i = 0; i < pinfo->nargs; i++)
	{
		if (pinfo->argnames[i] && strcmp(pinfo->argnames[i], paramname) == 0)
			return sql_fn_make_param(pinfo, i + 1, location);
	}

	return NULL;
}