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
struct TYPE_4__ {char* cmdfilter; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_cons_pal_update_event () ; 
 int r_core_cmd_file (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_file_exists (char const*) ; 

__attribute__((used)) static bool load_theme(RCore *core, const char *path) {
	if (!r_file_exists (path)) {
		return false;
	}
	core->cmdfilter = "ec ";
	bool res = r_core_cmd_file (core, path);
	if (res) {
		r_cons_pal_update_event ();
	}
	core->cmdfilter = NULL;
	return res;
}