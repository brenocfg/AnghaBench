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
struct __line_walk_param {scalar_t__ retval; int /*<<< orphan*/  data; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DWARF_CB_ABORT ; 
 int DWARF_CB_OK ; 
 scalar_t__ __die_walk_funclines (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __die_walk_culines_cb(Dwarf_Die *sp_die, void *data)
{
	struct __line_walk_param *lw = data;

	lw->retval = __die_walk_funclines(sp_die, true, lw->callback, lw->data);
	if (lw->retval != 0)
		return DWARF_CB_ABORT;

	return DWARF_CB_OK;
}