#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symlist_t ;
struct TYPE_8__ {TYPE_1__* symbol; } ;
typedef  TYPE_2__ symbol_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_2__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_2__* SLIST_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

symbol_node_t *
symlist_search(symlist_t *symlist, char *symname)
{
	symbol_node_t *curnode;

	curnode = SLIST_FIRST(symlist);
	while(curnode != NULL) {
		if (strcmp(symname, curnode->symbol->name) == 0)
			break;
		curnode = SLIST_NEXT(curnode, links);
	}
	return (curnode);
}