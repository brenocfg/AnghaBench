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
struct mp_cmd {int dummy; } ;
struct cmd_queue {int dummy; } ;
struct input_ctx {TYPE_1__* opts; struct cmd_queue cmd_queue; } ;
struct TYPE_2__ {scalar_t__ key_fifo_size; } ;

/* Variables and functions */
 scalar_t__ queue_count_cmds (struct cmd_queue*) ; 

__attribute__((used)) static bool should_drop_cmd(struct input_ctx *ictx, struct mp_cmd *cmd)
{
    struct cmd_queue *queue = &ictx->cmd_queue;
    return queue_count_cmds(queue) >= ictx->opts->key_fifo_size;
}