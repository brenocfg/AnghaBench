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
struct mp_refqueue {TYPE_1__* conv; int /*<<< orphan*/  in_format; } ;
struct TYPE_2__ {int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_refqueue_flush (struct mp_refqueue*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void refqueue_dtor(void *p)
{
    struct mp_refqueue *q = p;
    mp_refqueue_flush(q);
    mp_image_unrefp(&q->in_format);
    talloc_free(q->conv->f);
}