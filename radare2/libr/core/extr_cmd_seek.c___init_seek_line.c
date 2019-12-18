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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_config_bump (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int r_core_lines_initcache (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __init_seek_line(RCore *core) {
	ut64 from, to;

	r_config_bump (core->config, "lines.to");
	from = r_config_get_i (core->config, "lines.from");
	to = r_config_get_i (core->config, "lines.to");
	if (r_core_lines_initcache (core, from, to) == -1) {
		eprintf ("ERROR: \"lines.from\" and \"lines.to\" must be set\n");
	}
}