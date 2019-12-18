#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ft2_source {scalar_t__* text; int custom_width; int cx; int /*<<< orphan*/  font_face; int /*<<< orphan*/  word_wrap; int /*<<< orphan*/ * vbuf; int /*<<< orphan*/  max_h; int /*<<< orphan*/  cy; } ;
typedef  int /*<<< orphan*/  gs_vertbuffer_t ;
struct TYPE_2__ {scalar_t__ xadv; } ;
typedef  int /*<<< orphan*/  FT_UInt ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Get_Char_Index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * create_uv_vbuffer (int,int) ; 
 int /*<<< orphan*/  fill_vertex_buffer (struct ft2_source*) ; 
 int get_ft2_text_width (scalar_t__*,struct ft2_source*) ; 
 int /*<<< orphan*/  gs_vertexbuffer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 TYPE_1__* src_glyph ; 
 int wcslen (scalar_t__*) ; 

void set_up_vertex_buffer(struct ft2_source *srcdata)
{
	FT_UInt glyph_index = 0;
	uint32_t x = 0, space_pos = 0, word_width = 0;
	size_t len;

	if (!srcdata->text)
		return;

	if (srcdata->custom_width >= 100)
		srcdata->cx = srcdata->custom_width;
	else
		srcdata->cx = get_ft2_text_width(srcdata->text, srcdata);
	srcdata->cy = srcdata->max_h;

	obs_enter_graphics();
	if (srcdata->vbuf != NULL) {
		gs_vertbuffer_t *tmpvbuf = srcdata->vbuf;
		srcdata->vbuf = NULL;
		gs_vertexbuffer_destroy(tmpvbuf);
	}

	if (*srcdata->text == 0) {
		obs_leave_graphics();
		return;
	}

	srcdata->vbuf =
		create_uv_vbuffer((uint32_t)wcslen(srcdata->text) * 6, true);

	if (srcdata->custom_width <= 100)
		goto skip_word_wrap;
	if (!srcdata->word_wrap)
		goto skip_word_wrap;

	len = wcslen(srcdata->text);

	for (uint32_t i = 0; i <= len; i++) {
		if (i == wcslen(srcdata->text))
			goto eos_check;

		if (srcdata->text[i] != L' ' && srcdata->text[i] != L'\n')
			goto next_char;

	eos_check:;
		if (x + word_width > srcdata->custom_width) {
			if (space_pos != 0)
				srcdata->text[space_pos] = L'\n';
			x = 0;
		}
		if (i == wcslen(srcdata->text))
			goto eos_skip;

		x += word_width;
		word_width = 0;
		if (srcdata->text[i] == L'\n')
			x = 0;
		if (srcdata->text[i] == L' ')
			space_pos = i;
	next_char:;
		glyph_index =
			FT_Get_Char_Index(srcdata->font_face, srcdata->text[i]);
		word_width += src_glyph->xadv;
	eos_skip:;
	}

skip_word_wrap:;
	fill_vertex_buffer(srcdata);
	obs_leave_graphics();
}