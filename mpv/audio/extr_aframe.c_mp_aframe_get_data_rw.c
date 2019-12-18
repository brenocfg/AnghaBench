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
typedef  int /*<<< orphan*/  uint8_t ;
struct mp_aframe {TYPE_1__* av_frame; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** extended_data; } ;

/* Variables and functions */
 scalar_t__ av_frame_make_writable (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_aframe_is_allocated (struct mp_aframe*) ; 

uint8_t **mp_aframe_get_data_rw(struct mp_aframe *frame)
{
    if (!mp_aframe_is_allocated(frame))
        return NULL;
    if (av_frame_make_writable(frame->av_frame) < 0)
        return NULL;
    return frame->av_frame->extended_data;
}