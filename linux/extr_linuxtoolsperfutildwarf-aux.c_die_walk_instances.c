#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct __instance_walk_param {int (* callback ) (TYPE_1__*,void*) ;void* data; int retval; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ Dwarf_Die ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __die_walk_instances_cb ; 
 int /*<<< orphan*/  die_find_child (TYPE_1__*,int /*<<< orphan*/ ,struct __instance_walk_param*,TYPE_1__*) ; 
 int /*<<< orphan*/ * dwarf_diecu (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int die_walk_instances(Dwarf_Die *or_die, int (*callback)(Dwarf_Die *, void *),
		       void *data)
{
	Dwarf_Die cu_die;
	Dwarf_Die die_mem;
	struct __instance_walk_param iwp = {
		.addr = or_die->addr,
		.callback = callback,
		.data = data,
		.retval = -ENOENT,
	};

	if (dwarf_diecu(or_die, &cu_die, NULL, NULL) == NULL)
		return -ENOENT;

	die_find_child(&cu_die, __die_walk_instances_cb, &iwp, &die_mem);

	return iwp.retval;
}