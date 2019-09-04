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
 int /*<<< orphan*/  C ; 
 int /*<<< orphan*/  CC ; 
 int /*<<< orphan*/  CS ; 
 int /*<<< orphan*/  Cs ; 
 int /*<<< orphan*/  Cvb ; 
 int /*<<< orphan*/  Cvr ; 
 int /*<<< orphan*/  Cvs ; 
 int /*<<< orphan*/  DEFINE_CMD_DESCRIPTOR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_meta_init(RCore *core) {
	DEFINE_CMD_DESCRIPTOR (core, C);
	DEFINE_CMD_DESCRIPTOR (core, CC);
	DEFINE_CMD_DESCRIPTOR (core, CS);
	DEFINE_CMD_DESCRIPTOR (core, Cs);
	DEFINE_CMD_DESCRIPTOR (core, Cvb);
	DEFINE_CMD_DESCRIPTOR (core, Cvr);
	DEFINE_CMD_DESCRIPTOR (core, Cvs);
}