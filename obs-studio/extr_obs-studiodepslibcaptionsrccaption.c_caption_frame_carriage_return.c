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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  libcaption_stauts_t ;
struct TYPE_5__ {scalar_t__ row; int rup; scalar_t__ col; } ;
struct TYPE_6__ {int /*<<< orphan*/  write; TYPE_1__ state; } ;
typedef  TYPE_2__ caption_frame_t ;
typedef  int /*<<< orphan*/  caption_frame_cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_ERROR ; 
 int /*<<< orphan*/  LIBCAPTION_OK ; 
 int SCREEN_COLS ; 
 int SCREEN_ROWS ; 
 int /*<<< orphan*/  caption_frame_rollup (TYPE_2__*) ; 
 int /*<<< orphan*/ * frame_buffer_cell (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

libcaption_stauts_t caption_frame_carriage_return(caption_frame_t* frame)
{
    if (0 > frame->state.row || SCREEN_ROWS <= frame->state.row) {
        return LIBCAPTION_ERROR;
    }

    int r = frame->state.row - (frame->state.rup - 1);

    if (0 >= r || !caption_frame_rollup(frame)) {
        return LIBCAPTION_OK;
    }

    for (; r < SCREEN_ROWS; ++r) {
        uint8_t* dst = (uint8_t*)frame_buffer_cell(frame->write, r - 1, 0);
        uint8_t* src = (uint8_t*)frame_buffer_cell(frame->write, r - 0, 0);
        memcpy(dst, src, sizeof(caption_frame_cell_t) * SCREEN_COLS);
    }

    frame->state.col = 0;
    caption_frame_cell_t* cell = frame_buffer_cell(frame->write, SCREEN_ROWS - 1, 0);
    memset(cell, 0, sizeof(caption_frame_cell_t) * SCREEN_COLS);
    return LIBCAPTION_OK;
}