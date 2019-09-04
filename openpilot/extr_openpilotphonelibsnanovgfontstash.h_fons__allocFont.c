#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nfonts; int cfonts; TYPE_1__** fonts; } ;
struct TYPE_7__ {int cglyphs; scalar_t__ nglyphs; int /*<<< orphan*/ * glyphs; } ;
typedef  int /*<<< orphan*/  FONSglyph ;
typedef  TYPE_1__ FONSfont ;
typedef  TYPE_2__ FONScontext ;

/* Variables and functions */
 int FONS_INIT_GLYPHS ; 
 int FONS_INVALID ; 
 int /*<<< orphan*/  fons__freeFont (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (TYPE_1__**,int) ; 

__attribute__((used)) static int fons__allocFont(FONScontext* stash)
{
	FONSfont* font = NULL;
	if (stash->nfonts+1 > stash->cfonts) {
		stash->cfonts = stash->cfonts == 0 ? 8 : stash->cfonts * 2;
		stash->fonts = (FONSfont**)realloc(stash->fonts, sizeof(FONSfont*) * stash->cfonts);
		if (stash->fonts == NULL)
			return -1;
	}
	font = (FONSfont*)malloc(sizeof(FONSfont));
	if (font == NULL) goto error;
	memset(font, 0, sizeof(FONSfont));

	font->glyphs = (FONSglyph*)malloc(sizeof(FONSglyph) * FONS_INIT_GLYPHS);
	if (font->glyphs == NULL) goto error;
	font->cglyphs = FONS_INIT_GLYPHS;
	font->nglyphs = 0;

	stash->fonts[stash->nfonts++] = font;
	return stash->nfonts-1;

error:
	fons__freeFont(font);

	return FONS_INVALID;
}