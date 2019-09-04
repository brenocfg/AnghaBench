#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint32_t ;
struct ft2_source {int /*<<< orphan*/ * draw_effect; int /*<<< orphan*/ * vbuf; int /*<<< orphan*/ * tex; struct ft2_source* text_file; struct ft2_source* colorbuf; struct ft2_source* texbuf; struct ft2_source* text; struct ft2_source* font_style; struct ft2_source* font_name; struct ft2_source** cacheglyphs; int /*<<< orphan*/ * font_face; } ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (struct ft2_source*) ; 
 int /*<<< orphan*/  gs_effect_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_vertexbuffer_destroy (int /*<<< orphan*/ *) ; 
 size_t num_cache_slots ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void ft2_source_destroy(void *data)
{
	struct ft2_source *srcdata = data;

	if (srcdata->font_face != NULL) {
		FT_Done_Face(srcdata->font_face);
		srcdata->font_face = NULL;
	}

	for (uint32_t i = 0; i < num_cache_slots; i++) {
		if (srcdata->cacheglyphs[i] != NULL) {
			bfree(srcdata->cacheglyphs[i]);
			srcdata->cacheglyphs[i] = NULL;
		}
	}

	if (srcdata->font_name != NULL)
		bfree(srcdata->font_name);
	if (srcdata->font_style != NULL)
		bfree(srcdata->font_style);
	if (srcdata->text != NULL)
		bfree(srcdata->text);
	if (srcdata->texbuf != NULL)
		bfree(srcdata->texbuf);
	if (srcdata->colorbuf != NULL)
		bfree(srcdata->colorbuf);
	if (srcdata->text_file != NULL)
		bfree(srcdata->text_file);

	obs_enter_graphics();

	if (srcdata->tex != NULL) {
		gs_texture_destroy(srcdata->tex);
		srcdata->tex = NULL;
	}
	if (srcdata->vbuf != NULL) {
		gs_vertexbuffer_destroy(srcdata->vbuf);
		srcdata->vbuf = NULL;
	}
	if (srcdata->draw_effect != NULL) {
		gs_effect_destroy(srcdata->draw_effect);
		srcdata->draw_effect = NULL;
	}

	obs_leave_graphics();

	bfree(srcdata);
}