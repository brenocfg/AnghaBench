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
 int /*<<< orphan*/  DEFINE_CMD_DESCRIPTOR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fc ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  fz ; 

__attribute__((used)) static void cmd_flag_init(RCore *core) {
	DEFINE_CMD_DESCRIPTOR (core, f);
	DEFINE_CMD_DESCRIPTOR (core, fc);
	DEFINE_CMD_DESCRIPTOR (core, fd);
	DEFINE_CMD_DESCRIPTOR (core, fs);
	DEFINE_CMD_DESCRIPTOR (core, fz);
}