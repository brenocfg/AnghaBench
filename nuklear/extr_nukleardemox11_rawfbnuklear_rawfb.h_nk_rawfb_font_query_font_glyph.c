#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float const height; } ;
struct nk_user_font_glyph {float width; float height; float xadvance; void** uv; void* offset; TYPE_1__ info; struct nk_user_font_glyph* glyphs; } ;
struct nk_font_glyph {float x1; float x0; float y1; float y0; float xadvance; float u0; float v0; float u1; float v1; } ;
struct nk_font {float width; float height; float xadvance; void** uv; void* offset; TYPE_1__ info; struct nk_font* glyphs; } ;
typedef  int /*<<< orphan*/  nk_rune ;
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_2__ nk_handle ;

/* Variables and functions */
 int /*<<< orphan*/  NK_ASSERT (struct nk_user_font_glyph*) ; 
 int /*<<< orphan*/  NK_UNUSED (int /*<<< orphan*/  const) ; 
 struct nk_font_glyph* nk_font_find_glyph (struct nk_user_font_glyph*,int /*<<< orphan*/  const) ; 
 void* nk_vec2 (float,float) ; 

__attribute__((used)) static void
nk_rawfb_font_query_font_glyph(nk_handle handle, const float height,
    struct nk_user_font_glyph *glyph, const nk_rune codepoint,
    const nk_rune next_codepoint)
{
    float scale;
    const struct nk_font_glyph *g;
    struct nk_font *font;
    NK_ASSERT(glyph);
    NK_UNUSED(next_codepoint);

    font = (struct nk_font*)handle.ptr;
    NK_ASSERT(font);
    NK_ASSERT(font->glyphs);
    if (!font || !glyph)
        return;

    scale = height/font->info.height;
    g = nk_font_find_glyph(font, codepoint);
    glyph->width = (g->x1 - g->x0) * scale;
    glyph->height = (g->y1 - g->y0) * scale;
    glyph->offset = nk_vec2(g->x0 * scale, g->y0 * scale);
    glyph->xadvance = (g->xadvance * scale);
    glyph->uv[0] = nk_vec2(g->u0, g->v0);
    glyph->uv[1] = nk_vec2(g->u1, g->v1);
}