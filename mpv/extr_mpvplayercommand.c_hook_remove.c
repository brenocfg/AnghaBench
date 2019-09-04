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
struct hook_handler {int dummy; } ;
struct command_ctx {int num_hooks; struct hook_handler** hooks; } ;
struct MPContext {struct command_ctx* command_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct hook_handler**,int,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct hook_handler*) ; 

__attribute__((used)) static void hook_remove(struct MPContext *mpctx, struct hook_handler *h)
{
    struct command_ctx *cmd = mpctx->command_ctx;
    for (int n = 0; n < cmd->num_hooks; n++) {
        if (cmd->hooks[n] == h) {
            talloc_free(cmd->hooks[n]);
            MP_TARRAY_REMOVE_AT(cmd->hooks, cmd->num_hooks, n);
            return;
        }
    }
    assert(0);
}