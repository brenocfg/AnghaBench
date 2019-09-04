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
typedef  int /*<<< orphan*/  symlist_t ;
typedef  int /*<<< orphan*/  symbol_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 

void
symlist_merge(symlist_t *symlist_dest, symlist_t *symlist_src1,
	      symlist_t *symlist_src2)
{
	symbol_node_t *node;

	*symlist_dest = *symlist_src1;
	while((node = SLIST_FIRST(symlist_src2)) != NULL) {
		SLIST_REMOVE_HEAD(symlist_src2, links);
		SLIST_INSERT_HEAD(symlist_dest, node, links);
	}

	/* These are now empty */
	SLIST_INIT(symlist_src1);
	SLIST_INIT(symlist_src2);
}