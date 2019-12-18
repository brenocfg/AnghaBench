#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; } ;
struct TYPE_14__ {float itw; float ith; TYPE_1__ params; } ;
struct TYPE_13__ {int /*<<< orphan*/  font; } ;
struct TYPE_12__ {int xoff; int yoff; int x0; int y0; int x1; int y1; float xadv; int /*<<< orphan*/  index; } ;
struct TYPE_11__ {float x0; float y0; float x1; float y1; float s0; float t0; float s1; float t1; } ;
typedef  TYPE_2__ FONSquad ;
typedef  TYPE_3__ FONSglyph ;
typedef  TYPE_4__ FONSfont ;
typedef  TYPE_5__ FONScontext ;

/* Variables and functions */
 int FONS_ZERO_TOPLEFT ; 
 float fons__tt_getGlyphKernAdvance (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fons__getQuad(FONScontext* stash, FONSfont* font,
						   int prevGlyphIndex, FONSglyph* glyph,
						   float scale, float spacing, float* x, float* y, FONSquad* q)
{
	float rx,ry,xoff,yoff,x0,y0,x1,y1;

	if (prevGlyphIndex != -1) {
		float adv = fons__tt_getGlyphKernAdvance(&font->font, prevGlyphIndex, glyph->index) * scale;
		*x += (int)(adv + spacing + 0.5f);
	}

	// Each glyph has 2px border to allow good interpolation,
	// one pixel to prevent leaking, and one to allow good interpolation for rendering.
	// Inset the texture region by one pixel for correct interpolation.
	xoff = (short)(glyph->xoff+1);
	yoff = (short)(glyph->yoff+1);
	x0 = (float)(glyph->x0+1);
	y0 = (float)(glyph->y0+1);
	x1 = (float)(glyph->x1-1);
	y1 = (float)(glyph->y1-1);

	if (stash->params.flags & FONS_ZERO_TOPLEFT) {
		rx = (float)(int)(*x + xoff);
		ry = (float)(int)(*y + yoff);

		q->x0 = rx;
		q->y0 = ry;
		q->x1 = rx + x1 - x0;
		q->y1 = ry + y1 - y0;

		q->s0 = x0 * stash->itw;
		q->t0 = y0 * stash->ith;
		q->s1 = x1 * stash->itw;
		q->t1 = y1 * stash->ith;
	} else {
		rx = (float)(int)(*x + xoff);
		ry = (float)(int)(*y - yoff);

		q->x0 = rx;
		q->y0 = ry;
		q->x1 = rx + x1 - x0;
		q->y1 = ry - y1 + y0;

		q->s0 = x0 * stash->itw;
		q->t0 = y0 * stash->ith;
		q->s1 = x1 * stash->itw;
		q->t1 = y1 * stash->ith;
	}

	*x += (int)(glyph->xadv / 10.0f + 0.5f);
}