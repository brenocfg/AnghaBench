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
 int /*<<< orphan*/  COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rotate_panel_cmds (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  register_rotate ; 

void __rotate_register_cb (void *user, bool rev) {
	RCore *core = (RCore *)user;
	__rotate_panel_cmds (core, register_rotate, COUNT (register_rotate), "dr", rev);
}