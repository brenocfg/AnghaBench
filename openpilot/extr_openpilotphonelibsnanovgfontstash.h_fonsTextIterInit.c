#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  font; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {size_t nfonts; TYPE_6__** fonts; } ;
struct TYPE_13__ {size_t font; float size; int align; int /*<<< orphan*/  spacing; scalar_t__ blur; } ;
struct TYPE_12__ {short isize; short iblur; float x; float nextx; float y; float nexty; char const* str; char const* next; char const* end; int prevGlyphIndex; scalar_t__ codepoint; int /*<<< orphan*/  spacing; TYPE_6__* font; int /*<<< orphan*/  scale; } ;
typedef  TYPE_1__ FONStextIter ;
typedef  TYPE_2__ FONSstate ;
typedef  TYPE_3__ FONScontext ;

/* Variables and functions */
 int FONS_ALIGN_CENTER ; 
 int FONS_ALIGN_LEFT ; 
 int FONS_ALIGN_RIGHT ; 
 float fonsTextBounds (TYPE_3__*,float,float,char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* fons__getState (TYPE_3__*) ; 
 scalar_t__ fons__getVertAlign (TYPE_3__*,TYPE_6__*,int,short) ; 
 int /*<<< orphan*/  fons__tt_getPixelHeightScale (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

int fonsTextIterInit(FONScontext* stash, FONStextIter* iter,
					 float x, float y, const char* str, const char* end)
{
	FONSstate* state = fons__getState(stash);
	float width;

	memset(iter, 0, sizeof(*iter));

	if (stash == NULL) return 0;
	if (state->font < 0 || state->font >= stash->nfonts) return 0;
	iter->font = stash->fonts[state->font];
	if (iter->font->data == NULL) return 0;

	iter->isize = (short)(state->size*10.0f);
	iter->iblur = (short)state->blur;
	iter->scale = fons__tt_getPixelHeightScale(&iter->font->font, (float)iter->isize/10.0f);

	// Align horizontally
	if (state->align & FONS_ALIGN_LEFT) {
		// empty
	} else if (state->align & FONS_ALIGN_RIGHT) {
		width = fonsTextBounds(stash, x,y, str, end, NULL);
		x -= width;
	} else if (state->align & FONS_ALIGN_CENTER) {
		width = fonsTextBounds(stash, x,y, str, end, NULL);
		x -= width * 0.5f;
	}
	// Align vertically.
	y += fons__getVertAlign(stash, iter->font, state->align, iter->isize);

	if (end == NULL)
		end = str + strlen(str);

	iter->x = iter->nextx = x;
	iter->y = iter->nexty = y;
	iter->spacing = state->spacing;
	iter->str = str;
	iter->next = str;
	iter->end = end;
	iter->codepoint = 0;
	iter->prevGlyphIndex = -1;

	return 1;
}