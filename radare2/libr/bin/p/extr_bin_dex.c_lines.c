#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct r_bin_dex_obj_t {int /*<<< orphan*/ * lines_list; } ;
struct TYPE_5__ {TYPE_1__* o; } ;
struct TYPE_4__ {struct r_bin_dex_obj_t* bin_obj; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */

__attribute__((used)) static RList *lines(RBinFile *bf) {
	struct r_bin_dex_obj_t *dex = bf->o->bin_obj;
	/// XXX this is called more than once
	// r_sys_backtrace();
	return dex->lines_list;
	// return r_list_clone (dex->lines_list);
}