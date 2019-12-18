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
struct mp_cmd {int /*<<< orphan*/  mouse_y; int /*<<< orphan*/  mouse_x; scalar_t__ mouse_move; } ;
struct input_ctx {int /*<<< orphan*/  mouse_y; int /*<<< orphan*/  mouse_x; int /*<<< orphan*/  cmd_queue; } ;
typedef  struct mp_cmd mp_cmd_t ;

/* Variables and functions */
 struct mp_cmd* check_autorepeat (struct input_ctx*) ; 
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 struct mp_cmd* queue_remove_head (int /*<<< orphan*/ *) ; 

mp_cmd_t *mp_input_read_cmd(struct input_ctx *ictx)
{
    input_lock(ictx);
    struct mp_cmd *ret = queue_remove_head(&ictx->cmd_queue);
    if (!ret)
        ret = check_autorepeat(ictx);
    if (ret && ret->mouse_move) {
        ictx->mouse_x = ret->mouse_x;
        ictx->mouse_y = ret->mouse_y;
    }
    input_unlock(ictx);
    return ret;
}