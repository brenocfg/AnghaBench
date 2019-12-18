#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* device_voltexture_create ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 TYPE_2__* thread_graphics ; 

gs_texture_t *gs_voltexture_create(uint32_t width, uint32_t height,
				   uint32_t depth,
				   enum gs_color_format color_format,
				   uint32_t levels, const uint8_t **data,
				   uint32_t flags)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_voltexture_create"))
		return NULL;

	return graphics->exports.device_voltexture_create(graphics->device,
							  width, height, depth,
							  color_format, levels,
							  data, flags);
}