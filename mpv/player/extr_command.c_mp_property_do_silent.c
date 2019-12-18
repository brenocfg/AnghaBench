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
struct command_ctx {int silence_option_deprecations; int /*<<< orphan*/  properties; } ;
struct MPContext {int /*<<< orphan*/  log; struct command_ctx* command_ctx; } ;

/* Variables and functions */
 int M_PROPERTY_OK ; 
 scalar_t__ is_property_set (int,void*) ; 
 int m_property_do (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,void*,struct MPContext*) ; 
 int /*<<< orphan*/  mp_notify_property (struct MPContext*,char*) ; 

__attribute__((used)) static int mp_property_do_silent(const char *name, int action, void *val,
                                 struct MPContext *ctx)
{
    struct command_ctx *cmd = ctx->command_ctx;
    cmd->silence_option_deprecations += 1;
    int r = m_property_do(ctx->log, cmd->properties, name, action, val, ctx);
    cmd->silence_option_deprecations -= 1;
    if (r == M_PROPERTY_OK && is_property_set(action, val))
        mp_notify_property(ctx, (char *)name);
    return r;
}