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
struct mp_cmd {TYPE_1__* def; } ;
struct input_ctx {int /*<<< orphan*/  key_history; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_ignore; } ;

/* Variables and functions */
 struct mp_cmd* get_cmd_from_keys (struct input_ctx*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  key_buf_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  should_drop_cmd (struct input_ctx*,struct mp_cmd*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_cmd*) ; 
 int /*<<< orphan*/  update_mouse_section (struct input_ctx*) ; 

__attribute__((used)) static struct mp_cmd *resolve_key(struct input_ctx *ictx, int code)
{
    update_mouse_section(ictx);
    struct mp_cmd *cmd = get_cmd_from_keys(ictx, NULL, code);
    key_buf_add(ictx->key_history, code);
    if (cmd && !cmd->def->is_ignore && !should_drop_cmd(ictx, cmd))
        return cmd;
    talloc_free(cmd);
    return NULL;
}