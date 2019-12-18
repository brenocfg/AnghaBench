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
struct spsc_queue {size_t size; size_t mask; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int errno ; 
 size_t lwan_nextpow2 (size_t) ; 

int spsc_queue_init(struct spsc_queue *q, size_t size)
{
    if (size == 0)
        return -EINVAL;

    size = lwan_nextpow2(size);
    q->buffer = calloc(1 + size, sizeof(int));
    if (!q->buffer)
        return -errno;

    ATOMIC_INIT(q->head, 0);
    ATOMIC_INIT(q->tail, 0);

    q->size = size;
    q->mask = size - 1;

    return 0;
}