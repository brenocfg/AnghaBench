#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libcaption_stauts_t ;
struct TYPE_5__ {int col; int /*<<< orphan*/  row; } ;
struct TYPE_6__ {TYPE_1__ state; } ;
typedef  TYPE_2__ caption_frame_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIA608_CHAR_NULL ; 
 int /*<<< orphan*/  LIBCAPTION_READY ; 
 int /*<<< orphan*/  caption_frame_write_char (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eia608_style_white ; 

libcaption_stauts_t caption_frame_backspace(caption_frame_t* frame)
{
    // do not reverse wrap (tw 28:20)
    frame->state.col = (0 < frame->state.col) ? (frame->state.col - 1) : 0;
    caption_frame_write_char(frame, frame->state.row, frame->state.col, eia608_style_white, 0, EIA608_CHAR_NULL);
    return LIBCAPTION_READY;
}