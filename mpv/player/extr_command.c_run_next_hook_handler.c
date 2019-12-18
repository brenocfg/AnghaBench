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
struct hook_handler {int /*<<< orphan*/  type; } ;
struct command_ctx {int num_hooks; struct hook_handler** hooks; } ;
struct MPContext {struct command_ctx* command_ctx; } ;

/* Variables and functions */
 int invoke_hook_handler (struct MPContext*,struct hook_handler*) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int run_next_hook_handler(struct MPContext *mpctx, char *type, int index)
{
    struct command_ctx *cmd = mpctx->command_ctx;

    for (int n = index; n < cmd->num_hooks; n++) {
        struct hook_handler *h = cmd->hooks[n];
        if (strcmp(h->type, type) == 0)
            return invoke_hook_handler(mpctx, h);
    }

    mp_wakeup_core(mpctx); // finished hook
    return 0;
}