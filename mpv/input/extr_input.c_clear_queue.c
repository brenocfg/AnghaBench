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
struct mp_cmd {int dummy; } ;
struct cmd_queue {struct mp_cmd* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_remove (struct cmd_queue*,struct mp_cmd*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_cmd*) ; 

__attribute__((used)) static void clear_queue(struct cmd_queue *queue)
{
    while (queue->first) {
        struct mp_cmd *item = queue->first;
        queue_remove(queue, item);
        talloc_free(item);
    }
}