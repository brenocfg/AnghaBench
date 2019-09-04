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
typedef  int /*<<< orphan*/  utf8_char_t ;
typedef  int /*<<< orphan*/  eia608_style_t ;
struct TYPE_5__ {int /*<<< orphan*/  front; } ;
typedef  TYPE_1__ caption_frame_t ;
struct TYPE_6__ {int uln; int /*<<< orphan*/  const* data; int /*<<< orphan*/  sty; } ;
typedef  TYPE_2__ caption_frame_cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* EIA608_CHAR_NULL ; 
 int /*<<< orphan*/  eia608_style_white ; 
 TYPE_2__* frame_buffer_cell (int /*<<< orphan*/ *,int,int) ; 

const utf8_char_t* caption_frame_read_char(caption_frame_t* frame, int row, int col, eia608_style_t* style, int* underline)
{
    // always read from front
    caption_frame_cell_t* cell = frame_buffer_cell(&frame->front, row, col);

    if (!cell) {
        if (style) {
            (*style) = eia608_style_white;
        }

        if (underline) {
            (*underline) = 0;
        }

        return EIA608_CHAR_NULL;
    }

    if (style) {
        (*style) = cell->sty;
    }

    if (underline) {
        (*underline) = cell->uln;
    }

    return &cell->data[0];
}