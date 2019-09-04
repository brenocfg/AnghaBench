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
struct mp_refqueue {scalar_t__ num_queue; scalar_t__ pos; int /*<<< orphan*/  queue; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_INSERT_AT (struct mp_refqueue*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct mp_image*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void mp_refqueue_add_input(struct mp_refqueue *q, struct mp_image *img)
{
    assert(img);

    MP_TARRAY_INSERT_AT(q, q->queue, q->num_queue, 0, img);
    q->pos++;

    assert(q->pos >= 0 && q->pos < q->num_queue);
}