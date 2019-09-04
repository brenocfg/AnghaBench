#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  libcaption_stauts_t ;
typedef  int /*<<< orphan*/  eia608_style_t ;
struct TYPE_4__ {int row; int col; int uln; int /*<<< orphan*/  sty; } ;
struct TYPE_5__ {TYPE_1__ state; } ;
typedef  TYPE_2__ caption_frame_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_OK ; 
 scalar_t__ eia608_parse_preamble (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int*,int*) ; 

libcaption_stauts_t caption_frame_decode_preamble(caption_frame_t* frame, uint16_t cc_data)
{
    eia608_style_t sty;
    int row, col, chn, uln;

    if (eia608_parse_preamble(cc_data, &row, &col, &sty, &chn, &uln)) {
        frame->state.row = row;
        frame->state.col = col;
        frame->state.sty = sty;
        frame->state.uln = uln;
    }

    return LIBCAPTION_OK;
}