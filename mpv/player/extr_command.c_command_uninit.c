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
struct command_ctx {int /*<<< orphan*/  hotplug; int /*<<< orphan*/  cache_dump_cmd; } ;
struct MPContext {struct command_ctx* command_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ao_hotplug_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  overlay_uninit (struct MPContext*) ; 
 int /*<<< orphan*/  talloc_free (struct command_ctx*) ; 

void command_uninit(struct MPContext *mpctx)
{
    struct command_ctx *ctx = mpctx->command_ctx;

    assert(!ctx->cache_dump_cmd); // closing the demuxer must have aborted it

    overlay_uninit(mpctx);
    ao_hotplug_destroy(ctx->hotplug);

    talloc_free(mpctx->command_ctx);
    mpctx->command_ctx = NULL;
}