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
struct input_ctx {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_input_parse_cmd_strv (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  mp_input_queue_cmd (struct input_ctx*,int /*<<< orphan*/ ) ; 

void mp_input_run_cmd(struct input_ctx *ictx, const char **cmd)
{
    mp_input_queue_cmd(ictx, mp_input_parse_cmd_strv(ictx->log, cmd));
}