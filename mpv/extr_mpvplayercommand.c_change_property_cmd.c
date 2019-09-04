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
struct mp_cmd_ctx {int /*<<< orphan*/  mpctx; } ;

/* Variables and functions */
 int mp_property_do (char const*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_property_status (struct mp_cmd_ctx*,char const*,int) ; 

__attribute__((used)) static void change_property_cmd(struct mp_cmd_ctx *cmd,
                                const char *name, int action, void *arg)
{
    int r = mp_property_do(name, action, arg, cmd->mpctx);
    show_property_status(cmd, name, r);
}