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
struct TYPE_3__ {int /*<<< orphan*/  lib; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_lib_opendir (int /*<<< orphan*/ ,char*) ; 
 char* r_str_r2_prefix (char const*) ; 

__attribute__((used)) static void __openPluginsAt(RCore *core, const char *arg) {
	char *pdir = r_str_r2_prefix (arg);
	if (pdir) {
		r_lib_opendir (core->lib, pdir);
		free (pdir);
	}
}