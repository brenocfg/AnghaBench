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
struct find_flag_t {scalar_t__ at; TYPE_1__* win; } ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ offset; } ;
struct TYPE_4__ {scalar_t__ offset; } ;
typedef  TYPE_2__ RFlagItem ;
typedef  int /*<<< orphan*/  RFlag ;

/* Variables and functions */
 int /*<<< orphan*/  find_flag_after ; 
 int /*<<< orphan*/  r_flag_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct find_flag_t*) ; 

__attribute__((used)) static bool find_flag_after_foreach(RFlagItem *flag, void *user) {
	if (flag->size != 0) {
		return true;
	}

	RFlag *flags = (RFlag *)user;
	struct find_flag_t u = { .win = NULL, .at = flag->offset };
	r_flag_foreach (flags, find_flag_after, &u);
	if (u.win) {
		flag->size = u.win->offset - flag->offset;
	}
	return true;
}