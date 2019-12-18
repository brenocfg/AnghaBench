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
struct file_op_queue {int /*<<< orphan*/  count; struct file_op* tail; struct file_op* head; } ;
struct file_op {struct file_op* next; } ;

/* Variables and functions */

__attribute__((used)) static inline void queue_file_op( struct file_op_queue *queue, struct file_op *op )
{
    op->next = NULL;
    if (queue->tail) queue->tail->next = op;
    else queue->head = op;
    queue->tail = op;
    queue->count++;
}