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
struct TYPE_5__ {scalar_t__ row; scalar_t__ col; int /*<<< orphan*/  uln; int /*<<< orphan*/  sty; } ;
struct TYPE_6__ {TYPE_1__ state; } ;
typedef  TYPE_2__ caption_frame_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_OK ; 
 scalar_t__ SCREEN_COLS ; 
 scalar_t__ SCREEN_ROWS ; 
 scalar_t__ caption_frame_write_char (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

libcaption_stauts_t eia608_write_char(caption_frame_t* frame, char* c)
{
    if (0 == c || 0 == c[0] || SCREEN_ROWS <= frame->state.row || 0 > frame->state.row || SCREEN_COLS <= frame->state.col || 0 > frame->state.col) {
        // NO-OP
    } else if (caption_frame_write_char(frame, frame->state.row, frame->state.col, frame->state.sty, frame->state.uln, c)) {
        frame->state.col += 1;
    }

    return LIBCAPTION_OK;
}