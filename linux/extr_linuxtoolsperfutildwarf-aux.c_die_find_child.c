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
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DIE_FIND_CB_CHILD ; 
 int DIE_FIND_CB_END ; 
 int DIE_FIND_CB_SIBLING ; 
 int dwarf_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_siblingof (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

Dwarf_Die *die_find_child(Dwarf_Die *rt_die,
			  int (*callback)(Dwarf_Die *, void *),
			  void *data, Dwarf_Die *die_mem)
{
	Dwarf_Die child_die;
	int ret;

	ret = dwarf_child(rt_die, die_mem);
	if (ret != 0)
		return NULL;

	do {
		ret = callback(die_mem, data);
		if (ret == DIE_FIND_CB_END)
			return die_mem;

		if ((ret & DIE_FIND_CB_CHILD) &&
		    die_find_child(die_mem, callback, data, &child_die)) {
			memcpy(die_mem, &child_die, sizeof(Dwarf_Die));
			return die_mem;
		}
	} while ((ret & DIE_FIND_CB_SIBLING) &&
		 dwarf_siblingof(die_mem, die_mem) == 0);

	return NULL;
}