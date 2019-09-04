#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RConfig ;

/* Variables and functions */
 int /*<<< orphan*/  r_config_get_i (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_cons_is_interactive () ; 

__attribute__((used)) static bool mustSaveHistory(RConfig *c) {
	if (!r_config_get_i (c, "scr.histsave")) {
		return false;
	}
	if (!r_cons_is_interactive ()) {
		return false;
	}
	return true;
}