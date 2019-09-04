#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  front; int /*<<< orphan*/  back; int /*<<< orphan*/  xds; } ;
typedef  TYPE_1__ caption_frame_t ;

/* Variables and functions */
 int /*<<< orphan*/  caption_frame_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caption_frame_state_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  xds_init (int /*<<< orphan*/ *) ; 

void caption_frame_init(caption_frame_t* frame)
{
    xds_init(&frame->xds);
    caption_frame_state_clear(frame);
    caption_frame_buffer_clear(&frame->back);
    caption_frame_buffer_clear(&frame->front);
}