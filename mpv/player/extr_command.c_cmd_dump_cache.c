#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_cmd_ctx {TYPE_2__* args; } ;
struct TYPE_3__ {int /*<<< orphan*/  s; int /*<<< orphan*/  d; } ;
struct TYPE_4__ {TYPE_1__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  run_dump_cmd (struct mp_cmd_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_dump_cache(void *p)
{
    struct mp_cmd_ctx *cmd = p;

    run_dump_cmd(cmd, cmd->args[0].v.d, cmd->args[1].v.d, cmd->args[2].v.s);
}