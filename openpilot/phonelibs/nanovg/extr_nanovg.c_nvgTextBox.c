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
struct TYPE_6__ {int textAlign; scalar_t__ fontId; float lineHeight; } ;
struct TYPE_5__ {float width; char* next; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ NVGtextRow ;
typedef  TYPE_2__ NVGstate ;
typedef  int /*<<< orphan*/  NVGcontext ;

/* Variables and functions */
 scalar_t__ FONS_INVALID ; 
 int NVG_ALIGN_BASELINE ; 
 int NVG_ALIGN_BOTTOM ; 
 int NVG_ALIGN_CENTER ; 
 int NVG_ALIGN_LEFT ; 
 int NVG_ALIGN_MIDDLE ; 
 int NVG_ALIGN_RIGHT ; 
 int NVG_ALIGN_TOP ; 
 int /*<<< orphan*/  nvgText (int /*<<< orphan*/ *,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvgTextBreakLines (int /*<<< orphan*/ *,char const*,char const*,float,TYPE_1__*,int) ; 
 int /*<<< orphan*/  nvgTextMetrics (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*) ; 
 TYPE_2__* nvg__getState (int /*<<< orphan*/ *) ; 

void nvgTextBox(NVGcontext* ctx, float x, float y, float breakRowWidth, const char* string, const char* end)
{
	NVGstate* state = nvg__getState(ctx);
	NVGtextRow rows[2];
	int nrows = 0, i;
	int oldAlign = state->textAlign;
	int haling = state->textAlign & (NVG_ALIGN_LEFT | NVG_ALIGN_CENTER | NVG_ALIGN_RIGHT);
	int valign = state->textAlign & (NVG_ALIGN_TOP | NVG_ALIGN_MIDDLE | NVG_ALIGN_BOTTOM | NVG_ALIGN_BASELINE);
	float lineh = 0;

	if (state->fontId == FONS_INVALID) return;

	nvgTextMetrics(ctx, NULL, NULL, &lineh);

	state->textAlign = NVG_ALIGN_LEFT | valign;

	while ((nrows = nvgTextBreakLines(ctx, string, end, breakRowWidth, rows, 2))) {
		for (i = 0; i < nrows; i++) {
			NVGtextRow* row = &rows[i];
			if (haling & NVG_ALIGN_LEFT)
				nvgText(ctx, x, y, row->start, row->end);
			else if (haling & NVG_ALIGN_CENTER)
				nvgText(ctx, x + breakRowWidth*0.5f - row->width*0.5f, y, row->start, row->end);
			else if (haling & NVG_ALIGN_RIGHT)
				nvgText(ctx, x + breakRowWidth - row->width, y, row->start, row->end);
			y += lineh * state->lineHeight;
		}
		string = rows[nrows-1].next;
	}

	state->textAlign = oldAlign;
}