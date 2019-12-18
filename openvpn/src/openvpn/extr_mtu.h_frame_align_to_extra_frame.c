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
struct frame {scalar_t__ extra_link; scalar_t__ extra_frame; scalar_t__ align_adjust; } ;

/* Variables and functions */

__attribute__((used)) static inline void
frame_align_to_extra_frame(struct frame *frame)
{
    frame->align_adjust = frame->extra_frame + frame->extra_link;
}