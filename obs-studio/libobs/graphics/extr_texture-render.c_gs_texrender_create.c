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
struct gs_texture_render {int format; int zsformat; } ;
typedef  struct gs_texture_render gs_texrender_t ;
typedef  enum gs_zstencil_format { ____Placeholder_gs_zstencil_format } gs_zstencil_format ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 struct gs_texture_render* bzalloc (int) ; 

gs_texrender_t *gs_texrender_create(enum gs_color_format format,
				    enum gs_zstencil_format zsformat)
{
	struct gs_texture_render *texrender;
	texrender = bzalloc(sizeof(struct gs_texture_render));
	texrender->format = format;
	texrender->zsformat = zsformat;

	return texrender;
}