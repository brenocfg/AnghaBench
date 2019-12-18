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
struct TYPE_2__ {scalar_t__ num; } ;
struct mp_aframe {double speed; int /*<<< orphan*/  pts; scalar_t__ format; TYPE_1__ chmap; int /*<<< orphan*/  av_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 

void mp_aframe_reset(struct mp_aframe *frame)
{
    av_frame_unref(frame->av_frame);
    frame->chmap.num = 0;
    frame->format = 0;
    frame->pts = MP_NOPTS_VALUE;
    frame->speed = 1.0;
}