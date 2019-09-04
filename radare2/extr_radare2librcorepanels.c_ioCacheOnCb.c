#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  panels; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r_cons_any_key (char*) ; 
 int /*<<< orphan*/  setMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioCacheOnCb(void *user) {
	RCore *core = (RCore *)user;
	r_config_set_i (core->config, "io.cache", 1);
	(void)r_cons_any_key ("io.cache is on");
	setMode (core->panels, PANEL_MODE_DEFAULT);
	return 0;
}