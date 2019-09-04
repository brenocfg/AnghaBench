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
typedef  int /*<<< orphan*/  RConfigHold ;

/* Variables and functions */
 int /*<<< orphan*/  r_config_hold_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_config_hold_restore (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_anal_emul_restore(RCore *core, RConfigHold *hc) {
	r_config_hold_restore (hc);
	r_config_hold_free (hc);
}