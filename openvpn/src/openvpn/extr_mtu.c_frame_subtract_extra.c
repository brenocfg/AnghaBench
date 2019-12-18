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
struct frame {scalar_t__ extra_frame; int /*<<< orphan*/  extra_tun; } ;

/* Variables and functions */

void
frame_subtract_extra(struct frame *frame, const struct frame *src)
{
    frame->extra_frame -= src->extra_frame;
    frame->extra_tun   += src->extra_frame;
}