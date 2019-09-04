#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct exec_command_t {int /*<<< orphan*/  cmd; int /*<<< orphan*/  core; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ RFlagItem ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_block_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmd0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool exec_command_on_flag(RFlagItem *flg, void *u) {
	struct exec_command_t *user = (struct exec_command_t *)u;
	r_core_block_size (user->core, flg->size);
	r_core_seek (user->core, flg->offset, 1);
	r_core_cmd0 (user->core, user->cmd);
	return true;
}