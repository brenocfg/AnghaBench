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
struct TYPE_4__ {int /*<<< orphan*/  panels; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_file_reopen_debug (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  setRefreshAll (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  updateDisassemblyAddr (TYPE_1__*) ; 

__attribute__((used)) static int reloadCb(void *user) {
	RCore *core = (RCore *)user;
	r_core_file_reopen_debug (core, "");
	updateDisassemblyAddr (core);
	setRefreshAll (core->panels, false);
	return 0;
}