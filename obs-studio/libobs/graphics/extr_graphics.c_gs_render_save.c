#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct gs_tvertarray {int dummy; } ;
typedef  int /*<<< orphan*/  gs_vertbuffer_t ;
struct TYPE_14__ {scalar_t__ num; int /*<<< orphan*/  array; } ;
struct TYPE_13__ {int /*<<< orphan*/  array; } ;
struct TYPE_12__ {int /*<<< orphan*/  array; } ;
struct TYPE_16__ {TYPE_8__* vbd; TYPE_4__* texverts; TYPE_3__ verts; TYPE_2__ colors; TYPE_1__ norms; scalar_t__ using_immediate; } ;
typedef  TYPE_5__ graphics_t ;
struct TYPE_17__ {size_t num_tex; TYPE_10__* tvarray; scalar_t__ num; int /*<<< orphan*/  colors; int /*<<< orphan*/  normals; int /*<<< orphan*/  points; } ;
struct TYPE_15__ {int /*<<< orphan*/  array; int /*<<< orphan*/  num; } ;
struct TYPE_11__ {int width; int /*<<< orphan*/  array; } ;

/* Variables and functions */
 TYPE_10__* bmalloc (int) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  gs_vbdata_destroy (TYPE_8__*) ; 
 int /*<<< orphan*/ * gs_vertexbuffer_create (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_immediate_arrays (TYPE_5__*) ; 
 TYPE_5__* thread_graphics ; 

gs_vertbuffer_t *gs_render_save(void)
{
	graphics_t *graphics = thread_graphics;
	size_t num_tex, i;

	if (!gs_valid("gs_render_save"))
		return NULL;
	if (graphics->using_immediate)
		return NULL;

	if (!graphics->verts.num) {
		gs_vbdata_destroy(graphics->vbd);
		return NULL;
	}

	for (num_tex = 0; num_tex < 16; num_tex++)
		if (!graphics->texverts[num_tex].num)
			break;

	graphics->vbd->points = graphics->verts.array;
	graphics->vbd->normals = graphics->norms.array;
	graphics->vbd->colors = graphics->colors.array;
	graphics->vbd->num = graphics->verts.num;
	graphics->vbd->num_tex = num_tex;

	if (graphics->vbd->num_tex) {
		graphics->vbd->tvarray =
			bmalloc(sizeof(struct gs_tvertarray) * num_tex);

		for (i = 0; i < num_tex; i++) {
			graphics->vbd->tvarray[i].width = 2;
			graphics->vbd->tvarray[i].array =
				graphics->texverts[i].array;
		}
	}

	reset_immediate_arrays(graphics);

	return gs_vertexbuffer_create(graphics->vbd, 0);
}