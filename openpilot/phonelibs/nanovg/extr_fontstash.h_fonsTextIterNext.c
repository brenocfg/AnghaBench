#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int index; } ;
struct TYPE_6__ {char* next; char* str; char const* end; int prevGlyphIndex; int /*<<< orphan*/  nexty; int /*<<< orphan*/  nextx; int /*<<< orphan*/  spacing; int /*<<< orphan*/  scale; int /*<<< orphan*/  font; int /*<<< orphan*/  iblur; int /*<<< orphan*/  isize; int /*<<< orphan*/  codepoint; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  utf8state; } ;
typedef  TYPE_1__ FONStextIter ;
typedef  int /*<<< orphan*/  FONSquad ;
typedef  TYPE_2__ FONSglyph ;
typedef  int /*<<< orphan*/  FONScontext ;

/* Variables and functions */
 scalar_t__ fons__decutf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const) ; 
 TYPE_2__* fons__getGlyph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fons__getQuad (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int fonsTextIterNext(FONScontext* stash, FONStextIter* iter, FONSquad* quad)
{
	FONSglyph* glyph = NULL;
	const char* str = iter->next;
	iter->str = iter->next;

	if (str == iter->end)
		return 0;

	for (; str != iter->end; str++) {
		if (fons__decutf8(&iter->utf8state, &iter->codepoint, *(const unsigned char*)str))
			continue;
		str++;
		// Get glyph and quad
		iter->x = iter->nextx;
		iter->y = iter->nexty;
		glyph = fons__getGlyph(stash, iter->font, iter->codepoint, iter->isize, iter->iblur);
		if (glyph != NULL)
			fons__getQuad(stash, iter->font, iter->prevGlyphIndex, glyph, iter->scale, iter->spacing, &iter->nextx, &iter->nexty, quad);
		iter->prevGlyphIndex = glyph != NULL ? glyph->index : -1;
		break;
	}
	iter->next = str;

	return 1;
}