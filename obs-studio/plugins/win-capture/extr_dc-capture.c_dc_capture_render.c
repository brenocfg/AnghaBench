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
struct dc_capture {scalar_t__ texture_written; scalar_t__ valid; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  draw_texture (struct dc_capture*,int /*<<< orphan*/ *) ; 

void dc_capture_render(struct dc_capture *capture, gs_effect_t *effect)
{
	if (capture->valid && capture->texture_written)
		draw_texture(capture, effect);
}