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
typedef  scalar_t__ uint64_t ;
struct hook_handler {scalar_t__ seq; int active; int /*<<< orphan*/  type; int /*<<< orphan*/  client; } ;
struct command_ctx {int num_hooks; struct hook_handler** hooks; } ;
struct MPContext {struct command_ctx* command_ctx; } ;

/* Variables and functions */
 int MPV_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*) ; 
 int run_next_hook_handler (struct MPContext*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int mp_hook_continue(struct MPContext *mpctx, char *client, uint64_t id)
{
    struct command_ctx *cmd = mpctx->command_ctx;

    for (int n = 0; n < cmd->num_hooks; n++) {
        struct hook_handler *h = cmd->hooks[n];
        if (strcmp(h->client, client) == 0 && h->seq == id) {
            if (!h->active)
                break;
            h->active = false;
            return run_next_hook_handler(mpctx, h->type, n + 1);
        }
    }

    MP_ERR(mpctx, "invalid hook API usage\n");
    return MPV_ERROR_INVALID_PARAMETER;
}