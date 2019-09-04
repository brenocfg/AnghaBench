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
struct Queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dequeue (struct Queue*) ; 
 int /*<<< orphan*/  free (struct Queue*) ; 
 scalar_t__ queue_has_more_items (struct Queue*) ; 

void
queue_destroy(struct Queue * queue)
{
    if (queue == NULL)
        return;
    while (queue_has_more_items(queue))
        dequeue(queue);
    free(queue);
}