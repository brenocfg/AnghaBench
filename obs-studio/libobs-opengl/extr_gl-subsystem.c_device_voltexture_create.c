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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  const** uint32_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  const* gs_device_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 

gs_texture_t *device_voltexture_create(gs_device_t *device, uint32_t width,
				       uint32_t height, uint32_t depth,
				       enum gs_color_format color_format,
				       uint32_t levels, const uint8_t **data,
				       uint32_t flags)
{
	/* TODO */
	UNUSED_PARAMETER(device);
	UNUSED_PARAMETER(width);
	UNUSED_PARAMETER(height);
	UNUSED_PARAMETER(depth);
	UNUSED_PARAMETER(color_format);
	UNUSED_PARAMETER(levels);
	UNUSED_PARAMETER(data);
	UNUSED_PARAMETER(flags);
	return NULL;
}