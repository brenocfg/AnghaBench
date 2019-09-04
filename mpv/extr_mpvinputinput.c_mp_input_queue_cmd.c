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
struct input_ctx {int /*<<< orphan*/  cmd_queue; } ;
typedef  int /*<<< orphan*/  mp_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 int /*<<< orphan*/  mp_input_wakeup (struct input_ctx*) ; 
 int /*<<< orphan*/  queue_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mp_input_queue_cmd(struct input_ctx *ictx, mp_cmd_t *cmd)
{
    input_lock(ictx);
    if (cmd) {
        queue_add_tail(&ictx->cmd_queue, cmd);
        mp_input_wakeup(ictx);
    }
    input_unlock(ictx);
    return 1;
}