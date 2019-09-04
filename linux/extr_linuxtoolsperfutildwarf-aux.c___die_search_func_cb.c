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
struct __addr_die_search_param {int /*<<< orphan*/  die_mem; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DWARF_CB_ABORT ; 
 int DWARF_CB_OK ; 
 scalar_t__ DW_TAG_subprogram ; 
 scalar_t__ dwarf_haspc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __die_search_func_cb(Dwarf_Die *fn_die, void *data)
{
	struct __addr_die_search_param *ad = data;

	/*
	 * Since a declaration entry doesn't has given pc, this always returns
	 * function definition entry.
	 */
	if (dwarf_tag(fn_die) == DW_TAG_subprogram &&
	    dwarf_haspc(fn_die, ad->addr)) {
		memcpy(ad->die_mem, fn_die, sizeof(Dwarf_Die));
		return DWARF_CB_ABORT;
	}
	return DWARF_CB_OK;
}