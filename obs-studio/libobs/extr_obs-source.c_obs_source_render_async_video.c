#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ async_active; scalar_t__* async_textures; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_draw_async_texture (TYPE_1__*) ; 

__attribute__((used)) static inline void obs_source_render_async_video(obs_source_t *source)
{
	if (source->async_textures[0] && source->async_active)
		obs_source_draw_async_texture(source);
}