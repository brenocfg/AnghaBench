#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ignore; int applied; struct TYPE_7__* next; scalar_t__ sourceline; struct TYPE_7__* filename; int /*<<< orphan*/ * errmsg; struct TYPE_7__* value; struct TYPE_7__* name; } ;
typedef  TYPE_1__ ConfigVariable ;

/* Variables and functions */
 scalar_t__ guc_name_compare (TYPE_1__*,char const*) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 void* pstrdup (char const*) ; 

__attribute__((used)) static void
replace_auto_config_value(ConfigVariable **head_p, ConfigVariable **tail_p,
						  const char *name, const char *value)
{
	ConfigVariable *item,
			   *next,
			   *prev = NULL;

	/*
	 * Remove any existing match(es) for "name".  Normally there'd be at most
	 * one, but if external tools have modified the config file, there could
	 * be more.
	 */
	for (item = *head_p; item != NULL; item = next)
	{
		next = item->next;
		if (guc_name_compare(item->name, name) == 0)
		{
			/* found a match, delete it */
			if (prev)
				prev->next = next;
			else
				*head_p = next;
			if (next == NULL)
				*tail_p = prev;

			pfree(item->name);
			pfree(item->value);
			pfree(item->filename);
			pfree(item);
		}
		else
			prev = item;
	}

	/* Done if we're trying to delete it */
	if (value == NULL)
		return;

	/* OK, append a new entry */
	item = palloc(sizeof *item);
	item->name = pstrdup(name);
	item->value = pstrdup(value);
	item->errmsg = NULL;
	item->filename = pstrdup("");	/* new item has no location */
	item->sourceline = 0;
	item->ignore = false;
	item->applied = false;
	item->next = NULL;

	if (*head_p == NULL)
		*head_p = item;
	else
		(*tail_p)->next = item;
	*tail_p = item;
}