#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vec2 {int dummy; } ;
struct gs_vb_data {scalar_t__ points; scalar_t__ colors; TYPE_1__* tvarray; } ;
struct ft2_source {int* text; int max_h; int* colorbuf; int custom_width; int cy; int /*<<< orphan*/ * color; int /*<<< orphan*/  font_face; int /*<<< orphan*/  vbuf; } ;
struct TYPE_4__ {int xadv; int yoff; int h; int /*<<< orphan*/  v2; int /*<<< orphan*/  u2; int /*<<< orphan*/  v; int /*<<< orphan*/  u; scalar_t__ w; scalar_t__ xoff; } ;
struct TYPE_3__ {scalar_t__ array; } ;
typedef  int /*<<< orphan*/  FT_UInt ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Get_Char_Index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfree (int*) ; 
 int* bzalloc (int) ; 
 struct gs_vb_data* gs_vertexbuffer_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rect_colors2 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_v2_uv (struct vec2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_v3_rect (scalar_t__,float,float,float,float) ; 
 TYPE_2__* src_glyph ; 
 size_t wcslen (int*) ; 

void fill_vertex_buffer(struct ft2_source *srcdata)
{
	struct gs_vb_data *vdata = gs_vertexbuffer_get_data(srcdata->vbuf);
	if (vdata == NULL || !srcdata->text)
		return;

	struct vec2 *tvarray = (struct vec2 *)vdata->tvarray[0].array;
	uint32_t *col = (uint32_t *)vdata->colors;

	FT_UInt glyph_index = 0;

	uint32_t dx = 0, dy = srcdata->max_h, max_y = dy;
	uint32_t cur_glyph = 0;
	size_t len = wcslen(srcdata->text);

	if (srcdata->colorbuf != NULL) {
		bfree(srcdata->colorbuf);
		srcdata->colorbuf = NULL;
	}
	srcdata->colorbuf =
		bzalloc(sizeof(uint32_t) * wcslen(srcdata->text) * 6);
	for (size_t i = 0; i < len * 6; i++) {
		srcdata->colorbuf[i] = 0xFF000000;
	}

	for (size_t i = 0; i < len; i++) {
	add_linebreak:;
		if (srcdata->text[i] != L'\n')
			goto draw_glyph;
		dx = 0;
		i++;
		dy += srcdata->max_h + 4;
		if (i == wcslen(srcdata->text))
			goto skip_glyph;
		if (srcdata->text[i] == L'\n')
			goto add_linebreak;
	draw_glyph:;
		// Skip filthy dual byte Windows line breaks
		if (srcdata->text[i] == L'\r')
			goto skip_glyph;

		glyph_index =
			FT_Get_Char_Index(srcdata->font_face, srcdata->text[i]);
		if (src_glyph == NULL)
			goto skip_glyph;

		if (srcdata->custom_width < 100)
			goto skip_custom_width;

		if (dx + src_glyph->xadv > srcdata->custom_width) {
			dx = 0;
			dy += srcdata->max_h + 4;
		}

	skip_custom_width:;

		set_v3_rect(vdata->points + (cur_glyph * 6),
			    (float)dx + (float)src_glyph->xoff,
			    (float)dy - (float)src_glyph->yoff,
			    (float)src_glyph->w, (float)src_glyph->h);
		set_v2_uv(tvarray + (cur_glyph * 6), src_glyph->u, src_glyph->v,
			  src_glyph->u2, src_glyph->v2);
		set_rect_colors2(col + (cur_glyph * 6), srcdata->color[0],
				 srcdata->color[1]);
		dx += src_glyph->xadv;
		if (dy - (float)src_glyph->yoff + src_glyph->h > max_y)
			max_y = dy - src_glyph->yoff + src_glyph->h;
		cur_glyph++;
	skip_glyph:;
	}

	srcdata->cy = max_y;
}