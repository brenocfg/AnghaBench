#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct MPContext {TYPE_1__* command_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  hotplug; } ;

/* Variables and functions */
 int /*<<< orphan*/  ao_hotplug_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  overlay_uninit (struct MPContext*) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 

void command_uninit(struct MPContext *mpctx)
{
    overlay_uninit(mpctx);
    ao_hotplug_destroy(mpctx->command_ctx->hotplug);
    talloc_free(mpctx->command_ctx);
    mpctx->command_ctx = NULL;
}