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
 int /*<<< orphan*/  w ; 
 int /*<<< orphan*/  wA ; 
 int /*<<< orphan*/  wa ; 
 int /*<<< orphan*/  wc ; 
 int /*<<< orphan*/  we ; 
 int /*<<< orphan*/  wo ; 
 int /*<<< orphan*/  wop ; 
 int /*<<< orphan*/  wp ; 
 int /*<<< orphan*/  wt ; 
 int /*<<< orphan*/  wv ; 
 int /*<<< orphan*/  wx ; 

__attribute__((used)) static void cmd_write_init(RCore *core) {
	DEFINE_CMD_DESCRIPTOR (core, w);
	DEFINE_CMD_DESCRIPTOR (core, wa);
	DEFINE_CMD_DESCRIPTOR (core, wA);
	DEFINE_CMD_DESCRIPTOR (core, wc);
	DEFINE_CMD_DESCRIPTOR (core, we);
	DEFINE_CMD_DESCRIPTOR (core, wo);
	DEFINE_CMD_DESCRIPTOR (core, wop);
	DEFINE_CMD_DESCRIPTOR (core, wp);
	DEFINE_CMD_DESCRIPTOR (core, wt);
	DEFINE_CMD_DESCRIPTOR (core, wv);
	DEFINE_CMD_DESCRIPTOR (core, wx);
}