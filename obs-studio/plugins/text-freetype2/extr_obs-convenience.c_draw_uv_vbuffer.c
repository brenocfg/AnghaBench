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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gs_vertbuffer_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_technique_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_TRIS ; 
 int /*<<< orphan*/  gs_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * gs_effect_get_technique (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_load_indexbuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_load_vertexbuffer (int /*<<< orphan*/ *) ; 
 size_t gs_technique_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ gs_technique_begin_pass (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  gs_technique_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_end_pass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_vertexbuffer_flush (int /*<<< orphan*/ *) ; 

void draw_uv_vbuffer(gs_vertbuffer_t *vbuf, gs_texture_t *tex,
		     gs_effect_t *effect, uint32_t num_verts)
{
	gs_texture_t *texture = tex;
	gs_technique_t *tech = gs_effect_get_technique(effect, "Draw");
	gs_eparam_t *image = gs_effect_get_param_by_name(effect, "image");
	size_t passes;

	if (vbuf == NULL || tex == NULL)
		return;

	gs_vertexbuffer_flush(vbuf);
	gs_load_vertexbuffer(vbuf);
	gs_load_indexbuffer(NULL);

	passes = gs_technique_begin(tech);

	for (size_t i = 0; i < passes; i++) {
		if (gs_technique_begin_pass(tech, i)) {
			gs_effect_set_texture(image, texture);

			gs_draw(GS_TRIS, 0, num_verts);

			gs_technique_end_pass(tech);
		}
	}

	gs_technique_end(tech);
}