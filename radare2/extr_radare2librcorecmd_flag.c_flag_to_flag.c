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
struct flag_to_flag_t {scalar_t__ next; scalar_t__ offset; } ;
struct TYPE_3__ {scalar_t__ offset; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/  flag_to_flag_foreach ; 
 int /*<<< orphan*/  r_flag_foreach_glob (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct flag_to_flag_t*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (char const*,int /*<<< orphan*/ ) ; 
 char* r_str_trim_ro (char const*) ; 

__attribute__((used)) static int flag_to_flag(RCore *core, const char *glob) {
	r_return_val_if_fail (glob, 0);
	glob = r_str_trim_ro (glob);
	struct flag_to_flag_t u = { .next = UT64_MAX, .offset = core->offset };
	r_flag_foreach_glob (core->flags, glob, flag_to_flag_foreach, &u);
	if (u.next != UT64_MAX && u.next > core->offset) {
		return u.next - core->offset;
	}
	return 0;
}