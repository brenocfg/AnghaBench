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
struct mp_cmd {struct mp_cmd* queue_next; } ;
struct cmd_queue {struct mp_cmd* first; } ;

/* Variables and functions */

__attribute__((used)) static void queue_add_tail(struct cmd_queue *queue, struct mp_cmd *cmd)
{
    struct mp_cmd **p_prev = &queue->first;
    while (*p_prev)
        p_prev = &(*p_prev)->queue_next;
    *p_prev = cmd;
    cmd->queue_next = NULL;
}