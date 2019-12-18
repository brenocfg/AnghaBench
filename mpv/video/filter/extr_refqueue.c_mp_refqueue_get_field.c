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
struct mp_refqueue {int dummy; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
 struct mp_image* mp_refqueue_get (struct mp_refqueue*,int) ; 
 scalar_t__ mp_refqueue_is_top_field (struct mp_refqueue*) ; 
 scalar_t__ mp_refqueue_top_field_first (struct mp_refqueue*) ; 

struct mp_image *mp_refqueue_get_field(struct mp_refqueue *q, int pos)
{
    // If the current field is the second field (conceptually), then pos=1
    // needs to get the next frame. Similarly, pos=-1 needs to get the current
    // frame, so round towards negative infinity.
    int round = mp_refqueue_top_field_first(q) != mp_refqueue_is_top_field(q);
    int frame = (pos < 0 ? pos - (1 - round) : pos + round) / 2;
    return mp_refqueue_get(q, frame);
}