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
struct mp_refqueue {int pos; int second_field; int num_queue; int needed_past_frames; int /*<<< orphan*/ * queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_refqueue_has_output (struct mp_refqueue*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mp_refqueue_next(struct mp_refqueue *q)
{
    if (!mp_refqueue_has_output(q))
        return;

    q->pos--;
    q->second_field = false;

    assert(q->pos >= -1 && q->pos < q->num_queue);

    // Discard unneeded past frames.
    while (q->num_queue - (q->pos + 1) > q->needed_past_frames) {
        assert(q->num_queue > 0);
        talloc_free(q->queue[q->num_queue - 1]);
        q->num_queue--;
    }

    assert(q->pos >= -1 && q->pos < q->num_queue);
}