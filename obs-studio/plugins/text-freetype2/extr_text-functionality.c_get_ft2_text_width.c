#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  scalar_t__ uint32_t ;
struct ft2_source {TYPE_3__* font_face; } ;
struct TYPE_7__ {TYPE_2__* glyph; } ;
struct TYPE_5__ {int x; } ;
struct TYPE_6__ {TYPE_1__ advance; } ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  TYPE_2__* FT_GlyphSlot ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Get_Char_Index (TYPE_3__*,int) ; 
 int /*<<< orphan*/  FT_LOAD_DEFAULT ; 
 int /*<<< orphan*/  FT_Load_Glyph (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t wcslen (int*) ; 

uint32_t get_ft2_text_width(wchar_t *text, struct ft2_source *srcdata)
{
	FT_GlyphSlot slot = srcdata->font_face->glyph;
	FT_UInt glyph_index = 0;
	uint32_t w = 0, max_w = 0;
	size_t len;

	if (!text)
		return 0;

	len = wcslen(text);
	for (size_t i = 0; i < len; i++) {
		glyph_index = FT_Get_Char_Index(srcdata->font_face, text[i]);
		FT_Load_Glyph(srcdata->font_face, glyph_index, FT_LOAD_DEFAULT);

		if (text[i] == L'\n')
			w = 0;
		else {
			w += slot->advance.x >> 6;
			if (w > max_w)
				max_w = w;
		}
	}

	return max_w;
}