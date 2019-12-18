#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gs_vertbuffer_t ;
struct TYPE_6__ {size_t num; } ;
struct TYPE_5__ {int /*<<< orphan*/ * vbd; int /*<<< orphan*/ * immediate_vertbuffer; scalar_t__ using_immediate; TYPE_4__* texverts; TYPE_4__ verts; TYPE_4__ colors; TYPE_4__ norms; } ;
typedef  TYPE_1__ graphics_t ;
typedef  enum gs_draw_mode { ____Placeholder_gs_draw_mode } gs_draw_mode ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  da_free (TYPE_4__) ; 
 int /*<<< orphan*/  gs_draw (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_load_indexbuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_load_vertexbuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gs_render_save () ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  gs_vbdata_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_vertexbuffer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_vertexbuffer_flush (int /*<<< orphan*/ *) ; 
 size_t min_size (size_t,size_t) ; 
 int /*<<< orphan*/  reset_immediate_arrays (TYPE_1__*) ; 
 TYPE_1__* thread_graphics ; 

void gs_render_stop(enum gs_draw_mode mode)
{
	graphics_t *graphics = thread_graphics;
	size_t i, num;

	if (!gs_valid("gs_render_stop"))
		return;

	num = graphics->verts.num;
	if (!num) {
		if (!graphics->using_immediate) {
			da_free(graphics->verts);
			da_free(graphics->norms);
			da_free(graphics->colors);
			for (i = 0; i < 16; i++)
				da_free(graphics->texverts[i]);
			gs_vbdata_destroy(graphics->vbd);
		}

		return;
	}

	if (graphics->norms.num &&
	    (graphics->norms.num != graphics->verts.num)) {
		blog(LOG_ERROR, "gs_render_stop: normal count does "
				"not match vertex count");
		num = min_size(num, graphics->norms.num);
	}

	if (graphics->colors.num &&
	    (graphics->colors.num != graphics->verts.num)) {
		blog(LOG_ERROR, "gs_render_stop: color count does "
				"not match vertex count");
		num = min_size(num, graphics->colors.num);
	}

	if (graphics->texverts[0].num &&
	    (graphics->texverts[0].num != graphics->verts.num)) {
		blog(LOG_ERROR, "gs_render_stop: texture vertex count does "
				"not match vertex count");
		num = min_size(num, graphics->texverts[0].num);
	}

	if (graphics->using_immediate) {
		gs_vertexbuffer_flush(graphics->immediate_vertbuffer);

		gs_load_vertexbuffer(graphics->immediate_vertbuffer);
		gs_load_indexbuffer(NULL);
		gs_draw(mode, 0, (uint32_t)num);

		reset_immediate_arrays(graphics);
	} else {
		gs_vertbuffer_t *vb = gs_render_save();

		gs_load_vertexbuffer(vb);
		gs_load_indexbuffer(NULL);
		gs_draw(mode, 0, 0);

		gs_vertexbuffer_destroy(vb);
	}

	graphics->vbd = NULL;
}