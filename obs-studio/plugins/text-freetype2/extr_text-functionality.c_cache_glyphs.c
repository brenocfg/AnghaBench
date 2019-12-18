#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct glyph_info {int dummy; } ;
struct ft2_source {scalar_t__ texbuf_x; scalar_t__ texbuf_y; scalar_t__ max_h; int /*<<< orphan*/ * texbuf; int /*<<< orphan*/ * tex; TYPE_7__* font_face; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_13__ {TYPE_3__* glyph; } ;
struct TYPE_12__ {float u; float u2; float v; float v2; int xadv; int /*<<< orphan*/  xoff; int /*<<< orphan*/  yoff; scalar_t__ h; scalar_t__ w; } ;
struct TYPE_10__ {scalar_t__ width; scalar_t__ rows; int /*<<< orphan*/ * buffer; } ;
struct TYPE_9__ {int x; } ;
struct TYPE_11__ {TYPE_2__ bitmap; TYPE_1__ advance; int /*<<< orphan*/  bitmap_left; int /*<<< orphan*/  bitmap_top; } ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  TYPE_3__* FT_GlyphSlot ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Get_Char_Index (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_LOAD_DEFAULT ; 
 int /*<<< orphan*/  FT_Load_Glyph (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_RENDER_MODE_NORMAL ; 
 int /*<<< orphan*/  FT_Render_Glyph (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GS_A8 ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 size_t buf_pos ; 
 TYPE_4__* bzalloc (int) ; 
 size_t glyph_pos ; 
 int /*<<< orphan*/ * gs_texture_create (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 TYPE_4__* src_glyph ; 
 scalar_t__ texbuf_h ; 
 scalar_t__ texbuf_w ; 
 size_t wcslen (int /*<<< orphan*/ *) ; 

void cache_glyphs(struct ft2_source *srcdata, wchar_t *cache_glyphs)
{
	FT_GlyphSlot slot;
	FT_UInt glyph_index = 0;

	if (!srcdata->font_face || !cache_glyphs)
		return;

	slot = srcdata->font_face->glyph;

	uint32_t dx = srcdata->texbuf_x, dy = srcdata->texbuf_y;

	int32_t cached_glyphs = 0;
	size_t len = wcslen(cache_glyphs);

	for (size_t i = 0; i < len; i++) {
		glyph_index =
			FT_Get_Char_Index(srcdata->font_face, cache_glyphs[i]);

		if (src_glyph != NULL)
			goto skip_glyph;

		FT_Load_Glyph(srcdata->font_face, glyph_index, FT_LOAD_DEFAULT);
		FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

		uint32_t g_w = slot->bitmap.width;
		uint32_t g_h = slot->bitmap.rows;

		if (srcdata->max_h < g_h)
			srcdata->max_h = g_h;

		if (dx + g_w >= texbuf_w) {
			dx = 0;
			dy += srcdata->max_h + 1;
		}

		if (dy + g_h >= texbuf_h) {
			blog(LOG_WARNING,
			     "Out of space trying to render glyphs");
			break;
		}

		src_glyph = bzalloc(sizeof(struct glyph_info));
		src_glyph->u = (float)dx / (float)texbuf_w;
		src_glyph->u2 = (float)(dx + g_w) / (float)texbuf_w;
		src_glyph->v = (float)dy / (float)texbuf_h;
		src_glyph->v2 = (float)(dy + g_h) / (float)texbuf_h;
		src_glyph->w = g_w;
		src_glyph->h = g_h;
		src_glyph->yoff = slot->bitmap_top;
		src_glyph->xoff = slot->bitmap_left;
		src_glyph->xadv = slot->advance.x >> 6;

		for (uint32_t y = 0; y < g_h; y++) {
			for (uint32_t x = 0; x < g_w; x++)
				srcdata->texbuf[buf_pos] =
					slot->bitmap.buffer[glyph_pos];
		}

		dx += (g_w + 1);
		if (dx >= texbuf_w) {
			dx = 0;
			dy += srcdata->max_h;
		}

		cached_glyphs++;
	skip_glyph:;
	}

	srcdata->texbuf_x = dx;
	srcdata->texbuf_y = dy;

	if (cached_glyphs > 0) {

		obs_enter_graphics();

		if (srcdata->tex != NULL) {
			gs_texture_t *tmp_texture = NULL;
			tmp_texture = srcdata->tex;
			srcdata->tex = NULL;
			gs_texture_destroy(tmp_texture);
		}

		srcdata->tex = gs_texture_create(
			texbuf_w, texbuf_h, GS_A8, 1,
			(const uint8_t **)&srcdata->texbuf, 0);

		obs_leave_graphics();
	}
}