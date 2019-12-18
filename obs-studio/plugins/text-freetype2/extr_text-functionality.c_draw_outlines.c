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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  draw_uv_vbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gs_matrix_identity () ; 
 int /*<<< orphan*/  gs_matrix_pop () ; 
 int /*<<< orphan*/  gs_matrix_push () ; 
 int /*<<< orphan*/  gs_matrix_translate3f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 struct gs_vb_data* gs_vertexbuffer_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * offsets ; 
 scalar_t__ wcslen (int /*<<< orphan*/ ) ; 

void draw_outlines(struct ft2_source *srcdata)
{
	// Horrible (hopefully temporary) solution for outlines.
	uint32_t *tmp;

	struct gs_vb_data *vdata = gs_vertexbuffer_get_data(srcdata->vbuf);

	if (!srcdata->text)
		return;

	tmp = vdata->colors;
	vdata->colors = srcdata->colorbuf;

	gs_matrix_push();
	for (int32_t i = 0; i < 8; i++) {
		gs_matrix_translate3f(offsets[i * 2], offsets[(i * 2) + 1],
				      0.0f);
		draw_uv_vbuffer(srcdata->vbuf, srcdata->tex,
				srcdata->draw_effect,
				(uint32_t)wcslen(srcdata->text) * 6);
	}
	gs_matrix_identity();
	gs_matrix_pop();

	vdata->colors = tmp;
}