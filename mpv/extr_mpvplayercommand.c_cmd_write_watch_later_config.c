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
struct mp_cmd_ctx {struct MPContext* mpctx; } ;
struct MPContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_write_watch_later_conf (struct MPContext*) ; 

__attribute__((used)) static void cmd_write_watch_later_config(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    mp_write_watch_later_conf(mpctx);
}