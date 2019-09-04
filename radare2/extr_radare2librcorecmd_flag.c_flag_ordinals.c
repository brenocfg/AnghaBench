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
struct rename_flag_t {char* pfx; int /*<<< orphan*/  count; TYPE_1__* core; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_flag_foreach_glob (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct rename_flag_t*) ; 
 char* r_str_trim_ro (char const*) ; 
 int /*<<< orphan*/  rename_flag_ordinal ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void flag_ordinals(RCore *core, const char *str) {
	const char *glob = r_str_trim_ro (str);
	char *pfx = strdup (glob);
	char *p = strchr (pfx, '*');
	if (p) {
		*p = 0;
	}

	struct rename_flag_t u = { .core = core, .pfx = pfx, .count = 0 };
	r_flag_foreach_glob (core->flags, glob, rename_flag_ordinal, &u);
	free (pfx);
}