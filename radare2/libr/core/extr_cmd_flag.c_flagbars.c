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
struct flagbar_t {int cols; TYPE_1__* core; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  flagbar_foreach ; 
 int r_cons_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_flag_foreach_space_glob (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flagbar_t*) ; 
 int /*<<< orphan*/  r_flag_space_cur (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flagbars(RCore *core, const char *glob) {
	int cols = r_cons_get_size (NULL);
	cols -= 80;
	if (cols < 0) {
		cols += 80;
	}

	struct flagbar_t u = { .core = core, .cols = cols };
	r_flag_foreach_space_glob (core->flags, glob, r_flag_space_cur (core->flags), flagbar_foreach, &u);
}