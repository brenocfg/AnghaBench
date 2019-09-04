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
struct mp_refqueue {int /*<<< orphan*/  filter; int /*<<< orphan*/  out; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_FRAME (int /*<<< orphan*/ ,struct mp_image*) ; 
 int /*<<< orphan*/  MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  MP_WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_refqueue_next_field (struct mp_refqueue*) ; 

void mp_refqueue_write_out_pin(struct mp_refqueue *q, struct mp_image *mpi)
{
    if (mpi) {
        mp_pin_in_write(q->out, MAKE_FRAME(MP_FRAME_VIDEO, mpi));
    } else {
        MP_WARN(q->filter, "failed to output frame\n");
        mp_filter_internal_mark_failed(q->filter);
    }
    mp_refqueue_next_field(q);
}