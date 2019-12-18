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
typedef  int uint32_t ;
struct gs_vb_data {int* colors; } ;
struct ft2_source {int* colorbuf; int /*<<< orphan*/  text; int /*<<< orphan*/  draw_effect; int /*<<< orphan*/  tex; int /*<<< orphan*/  vbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  draw_uv_vbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gs_matrix_identity () ; 
 int /*<<< orphan*/  gs_matrix_pop () ; 
 int /*<<< orphan*/  gs_matrix_push () ; 
 int /*<<< orphan*/  gs_matrix_translate3f (float,float,float) ; 
 struct gs_vb_data* gs_vertexbuffer_get_data (int /*<<< orphan*/ ) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ ) ; 

void draw_drop_shadow(struct ft2_source *srcdata)
{
	// Horrible (hopefully temporary) solution for drop shadow.
	uint32_t *tmp;

	struct gs_vb_data *vdata = gs_vertexbuffer_get_data(srcdata->vbuf);

	if (!srcdata->text)
		return;

	tmp = vdata->colors;
	vdata->colors = srcdata->colorbuf;

	gs_matrix_push();
	gs_matrix_translate3f(4.0f, 4.0f, 0.0f);
	draw_uv_vbuffer(srcdata->vbuf, srcdata->tex, srcdata->draw_effect,
			(uint32_t)wcslen(srcdata->text) * 6);
	gs_matrix_identity();
	gs_matrix_pop();

	vdata->colors = tmp;
}