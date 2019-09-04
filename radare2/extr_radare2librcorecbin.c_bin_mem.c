#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bin; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 scalar_t__ IS_MODE_JSON (int) ; 
 scalar_t__ IS_MODE_RAD (int) ; 
 scalar_t__ IS_MODE_SET (int) ; 
 int R_MODE_JSON ; 
 int /*<<< orphan*/  bin_mem_print (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * r_bin_get_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_print (char*) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 

__attribute__((used)) static int bin_mem(RCore *r, int mode) {
	RList *mem = NULL;
	if (!r) {
		return false;
	}
	if (!IS_MODE_JSON (mode)) {
		if (!(IS_MODE_RAD (mode) || IS_MODE_SET (mode))) {
			r_cons_println ("[Memory]\n");
		}
	}
	if (!(mem = r_bin_get_mem (r->bin))) {
		if (IS_MODE_JSON (mode)) {
			r_cons_print("[]");
		}
		return false;
	}
	if (IS_MODE_JSON (mode)) {
		r_cons_print ("[");
		bin_mem_print (mem, 7, 0, R_MODE_JSON);
		r_cons_println ("]");
		return true;
	} else if (!(IS_MODE_RAD (mode) || IS_MODE_SET (mode))) {
		bin_mem_print (mem, 7, 0, mode);
	}
	return true;
}