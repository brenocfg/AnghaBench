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
struct command_ctx {scalar_t__ hotplug; } ;
struct MPContext {struct command_ctx* command_ctx; } ;

/* Variables and functions */
 scalar_t__ ao_hotplug_check_update (scalar_t__) ; 
 int /*<<< orphan*/  cache_dump_poll (struct MPContext*) ; 
 int /*<<< orphan*/  mp_notify_property (struct MPContext*,char*) ; 

void handle_command_updates(struct MPContext *mpctx)
{
    struct command_ctx *ctx = mpctx->command_ctx;

    // This is a bit messy: ao_hotplug wakes up the player, and then we have
    // to recheck the state. Then the client(s) will read the property.
    if (ctx->hotplug && ao_hotplug_check_update(ctx->hotplug))
        mp_notify_property(mpctx, "audio-device-list");

    // Depends on polling demuxer wakeup callback notifications.
    cache_dump_poll(mpctx);
}