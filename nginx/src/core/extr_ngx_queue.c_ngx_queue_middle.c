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
typedef  int /*<<< orphan*/  ngx_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_queue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_queue_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_queue_next (int /*<<< orphan*/ *) ; 

ngx_queue_t *
ngx_queue_middle(ngx_queue_t *queue)
{
    ngx_queue_t  *middle, *next;

    middle = ngx_queue_head(queue);

    if (middle == ngx_queue_last(queue)) {
        return middle;
    }

    next = ngx_queue_head(queue);

    for ( ;; ) {
        middle = ngx_queue_next(middle);

        next = ngx_queue_next(next);

        if (next == ngx_queue_last(queue)) {
            return middle;
        }

        next = ngx_queue_next(next);

        if (next == ngx_queue_last(queue)) {
            return middle;
        }
    }
}