#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * async_textures; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 int /*<<< orphan*/  GS_DYNAMIC ; 
 int /*<<< orphan*/  gs_texture_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_get_height (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_get_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void recreate_async_texture(obs_source_t *source,
				   enum gs_color_format format)
{
	uint32_t cx = gs_texture_get_width(source->async_textures[0]);
	uint32_t cy = gs_texture_get_height(source->async_textures[0]);
	gs_texture_destroy(source->async_textures[0]);
	source->async_textures[0] =
		gs_texture_create(cx, cy, format, 1, NULL, GS_DYNAMIC);
}