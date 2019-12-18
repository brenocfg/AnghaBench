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
struct mp_refqueue {int /*<<< orphan*/  in_format; struct mp_image* next; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  mp_image_new_ref (struct mp_image*) ; 
 int /*<<< orphan*/  mp_image_unref_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_refqueue_add_input (struct mp_refqueue*,struct mp_image*) ; 
 int /*<<< orphan*/  mp_refqueue_flush (struct mp_refqueue*) ; 
 scalar_t__ mp_refqueue_has_output (struct mp_refqueue*) ; 

struct mp_image *mp_refqueue_execute_reinit(struct mp_refqueue *q)
{
    if (mp_refqueue_has_output(q) || !q->next)
        return NULL;

    struct mp_image *cur = q->next;
    q->next = NULL;

    mp_image_unrefp(&q->in_format);
    mp_refqueue_flush(q);

    q->in_format = mp_image_new_ref(cur);
    if (!q->in_format)
        abort();
    mp_image_unref_data(q->in_format);

    mp_refqueue_add_input(q, cur);
    return cur;
}