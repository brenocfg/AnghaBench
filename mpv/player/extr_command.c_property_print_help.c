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
struct command_ctx {int /*<<< orphan*/  properties; } ;
struct MPContext {int /*<<< orphan*/  log; struct command_ctx* command_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_properties_print_help_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void property_print_help(struct MPContext *mpctx)
{
    struct command_ctx *ctx = mpctx->command_ctx;
    m_properties_print_help_list(mpctx->log, ctx->properties);
}