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
struct TYPE_8__ {int /*<<< orphan*/  nfonts; scalar_t__ nscratch; TYPE_1__** fonts; } ;
struct TYPE_7__ {char* name; int* lut; int dataSize; unsigned char* data; unsigned char freeData; float ascender; float descender; float lineh; int /*<<< orphan*/  font; } ;
typedef  TYPE_1__ FONSfont ;
typedef  TYPE_2__ FONScontext ;

/* Variables and functions */
 int FONS_HASH_LUT_SIZE ; 
 int FONS_INVALID ; 
 int fons__allocFont (TYPE_2__*) ; 
 int /*<<< orphan*/  fons__freeFont (TYPE_1__*) ; 
 int /*<<< orphan*/  fons__tt_getFontVMetrics (int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  fons__tt_loadFont (TYPE_2__*,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int fonsAddFontMem(FONScontext* stash, const char* name, unsigned char* data, int dataSize, int freeData)
{
	int i, ascent, descent, fh, lineGap;
	FONSfont* font;

	int idx = fons__allocFont(stash);
	if (idx == FONS_INVALID)
		return FONS_INVALID;

	font = stash->fonts[idx];

	strncpy(font->name, name, sizeof(font->name));
	font->name[sizeof(font->name)-1] = '\0';

	// Init hash lookup.
	for (i = 0; i < FONS_HASH_LUT_SIZE; ++i)
		font->lut[i] = -1;

	// Read in the font data.
	font->dataSize = dataSize;
	font->data = data;
	font->freeData = (unsigned char)freeData;

	// Init font
	stash->nscratch = 0;
	if (!fons__tt_loadFont(stash, &font->font, data, dataSize)) goto error;

	// Store normalized line height. The real line height is got
	// by multiplying the lineh by font size.
	fons__tt_getFontVMetrics( &font->font, &ascent, &descent, &lineGap);
	fh = ascent - descent;
	font->ascender = (float)ascent / (float)fh;
	font->descender = (float)descent / (float)fh;
	font->lineh = (float)(fh + lineGap) / (float)fh;

	return idx;

error:
	fons__freeFont(font);
	stash->nfonts--;
	return FONS_INVALID;
}