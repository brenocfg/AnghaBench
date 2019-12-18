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
struct TYPE_4__ {int /*<<< orphan*/  gdbr_lock; } ;
typedef  TYPE_1__ libgdbr_t ;

/* Variables and functions */
 scalar_t__ _isbreaked ; 
 int /*<<< orphan*/  gdbr_break_process ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* r_cons_sleep_begin () ; 
 int /*<<< orphan*/  r_cons_sleep_end (void*) ; 
 int /*<<< orphan*/  r_th_lock_enter (int /*<<< orphan*/ ) ; 

bool gdbr_lock_enter(libgdbr_t *g) {
	r_cons_break_push (gdbr_break_process, g);
	void *bed = r_cons_sleep_begin ();
	r_th_lock_enter (g->gdbr_lock);
	r_cons_sleep_end (bed);
	if (_isbreaked) {
		return false;
	}
	return true;
}