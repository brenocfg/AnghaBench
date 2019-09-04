#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int blocksize; int /*<<< orphan*/  block; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  core_anal_bytes (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  r_core_block_size (TYPE_1__*,int) ; 
 scalar_t__ r_num_get (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void cmd_anal_bytes(RCore *core, const char *input) {
	int len = core->blocksize;
	int tbs = len;
	if (input[0]) {
		len = (int)r_num_get (core->num, input + 1);
		if (len > tbs) {
			r_core_block_size (core, len);
		}
	}
	core_anal_bytes (core, core->block, len, 0, input[0]);
	if (tbs != core->blocksize) {
		r_core_block_size (core, tbs);
	}
}