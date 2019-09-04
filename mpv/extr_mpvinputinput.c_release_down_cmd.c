#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct input_ctx {int ar_state; scalar_t__ last_key_down_time; scalar_t__ last_key_down; TYPE_2__* current_down_cmd; int /*<<< orphan*/  key_history; } ;
struct TYPE_5__ {int is_up; TYPE_1__* def; scalar_t__ emit_on_up; } ;
struct TYPE_4__ {scalar_t__ on_updown; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_input_queue_cmd (struct input_ctx*,TYPE_2__*) ; 
 int /*<<< orphan*/  talloc_free (TYPE_2__*) ; 
 int /*<<< orphan*/  update_mouse_section (struct input_ctx*) ; 

__attribute__((used)) static void release_down_cmd(struct input_ctx *ictx, bool drop_current)
{
    if (ictx->current_down_cmd && ictx->current_down_cmd->emit_on_up &&
        (!drop_current || ictx->current_down_cmd->def->on_updown))
    {
        memset(ictx->key_history, 0, sizeof(ictx->key_history));
        ictx->current_down_cmd->is_up = true;
        mp_input_queue_cmd(ictx, ictx->current_down_cmd);
    } else {
        talloc_free(ictx->current_down_cmd);
    }
    ictx->current_down_cmd = NULL;
    ictx->last_key_down = 0;
    ictx->last_key_down_time = 0;
    ictx->ar_state = -1;
    update_mouse_section(ictx);
}