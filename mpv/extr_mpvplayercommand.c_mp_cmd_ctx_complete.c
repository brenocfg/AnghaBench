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
struct mp_cmd_ctx {int completed; int /*<<< orphan*/  result; scalar_t__ abort; int /*<<< orphan*/  mpctx; int /*<<< orphan*/  (* on_completion ) (struct mp_cmd_ctx*) ;int /*<<< orphan*/  success; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_abort_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mpv_free_node_contents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mp_cmd_ctx*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_cmd_ctx*) ; 

void mp_cmd_ctx_complete(struct mp_cmd_ctx *cmd)
{
    cmd->completed = true;
    if (!cmd->success)
        mpv_free_node_contents(&cmd->result);
    if (cmd->on_completion)
        cmd->on_completion(cmd);
    if (cmd->abort)
        mp_abort_remove(cmd->mpctx, cmd->abort);
    mpv_free_node_contents(&cmd->result);
    talloc_free(cmd);
}