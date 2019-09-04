#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libcaption_stauts_t ;
struct TYPE_3__ {int /*<<< orphan*/  back; int /*<<< orphan*/  front; } ;
typedef  TYPE_1__ caption_frame_t ;
typedef  int /*<<< orphan*/  caption_frame_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_READY ; 
 int /*<<< orphan*/  caption_frame_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

libcaption_stauts_t caption_frame_end(caption_frame_t* frame)
{
    memcpy(&frame->front, &frame->back, sizeof(caption_frame_buffer_t));
    caption_frame_buffer_clear(&frame->back); // This is required
    return LIBCAPTION_READY;
}