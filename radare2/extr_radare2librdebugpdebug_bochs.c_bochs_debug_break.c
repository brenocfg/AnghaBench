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

/* Variables and functions */
 int bBreak ; 
 int /*<<< orphan*/  bochs_cmd_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  eprintf (char*) ; 

__attribute__((used)) static void bochs_debug_break(void *u) {
	eprintf("bochs_debug_break: Sending break...\n");
	bochs_cmd_stop (desc);
	bBreak = true;
}