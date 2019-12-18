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
struct TYPE_4__ {scalar_t__ itemtype; struct TYPE_4__* prev; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ PLpgSQL_nsitem ;

/* Variables and functions */
 scalar_t__ PLPGSQL_NSTYPE_LABEL ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

PLpgSQL_nsitem *
plpgsql_ns_lookup_label(PLpgSQL_nsitem *ns_cur, const char *name)
{
	while (ns_cur != NULL)
	{
		if (ns_cur->itemtype == PLPGSQL_NSTYPE_LABEL &&
			strcmp(ns_cur->name, name) == 0)
			return ns_cur;
		ns_cur = ns_cur->prev;
	}

	return NULL;				/* label not found */
}