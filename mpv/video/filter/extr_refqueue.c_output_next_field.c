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
struct mp_refqueue {int second_field; int flags; size_t pos; TYPE_1__** queue; } ;
struct TYPE_2__ {double pts; } ;

/* Variables and functions */
 int MP_MODE_OUTPUT_FIELDS ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_refqueue_should_deint (struct mp_refqueue*) ; 

__attribute__((used)) static bool output_next_field(struct mp_refqueue *q)
{
    if (q->second_field)
        return false;
    if (!(q->flags & MP_MODE_OUTPUT_FIELDS))
        return false;
    if (!mp_refqueue_should_deint(q))
        return false;

    assert(q->pos >= 0);

    // If there's no (reasonable) timestamp, also skip the field.
    if (q->pos == 0)
        return false;

    double pts = q->queue[q->pos]->pts;
    double next_pts = q->queue[q->pos - 1]->pts;
    if (pts == MP_NOPTS_VALUE || next_pts == MP_NOPTS_VALUE)
        return false;

    double frametime = next_pts - pts;
    if (frametime <= 0.0 || frametime >= 1.0)
        return false;

    q->queue[q->pos]->pts = pts + frametime / 2;
    q->second_field = true;
    return true;
}