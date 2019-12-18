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
struct ft2_source {scalar_t__* text; int /*<<< orphan*/  draw_effect; int /*<<< orphan*/ * tex; int /*<<< orphan*/ * vbuf; scalar_t__ drop_shadow; scalar_t__ outline_text; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  draw_drop_shadow (struct ft2_source*) ; 
 int /*<<< orphan*/  draw_outlines (struct ft2_source*) ; 
 int /*<<< orphan*/  draw_uv_vbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gs_reset_blend_state () ; 
 scalar_t__ wcslen (scalar_t__*) ; 

__attribute__((used)) static void ft2_source_render(void *data, gs_effect_t *effect)
{
	struct ft2_source *srcdata = data;
	if (srcdata == NULL)
		return;

	if (srcdata->tex == NULL || srcdata->vbuf == NULL)
		return;
	if (srcdata->text == NULL || *srcdata->text == 0)
		return;

	gs_reset_blend_state();
	if (srcdata->outline_text)
		draw_outlines(srcdata);
	if (srcdata->drop_shadow)
		draw_drop_shadow(srcdata);

	draw_uv_vbuffer(srcdata->vbuf, srcdata->tex, srcdata->draw_effect,
			(uint32_t)wcslen(srcdata->text) * 6);

	UNUSED_PARAMETER(effect);
}