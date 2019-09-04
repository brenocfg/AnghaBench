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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int r_core_cmd0 (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int core_cmd0_wrapper(void *core, const char *cmd) {
	return r_core_cmd0 ((RCore *)core, cmd);
}