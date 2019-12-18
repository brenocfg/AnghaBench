#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  texture; } ;
struct TYPE_3__ {TYPE_2__ image; } ;
struct image_source {TYPE_1__ if2; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void image_source_render(void *data, gs_effect_t *effect)
{
	struct image_source *context = data;

	if (!context->if2.image.texture)
		return;

	gs_effect_set_texture(gs_effect_get_param_by_name(effect, "image"),
			      context->if2.image.texture);
	gs_draw_sprite(context->if2.image.texture, 0, context->if2.image.cx,
		       context->if2.image.cy);
}