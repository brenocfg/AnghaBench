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
typedef  void* uint32_t ;
struct color_source {void* height; void* width; void* color; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_get_int (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void color_source_update(void *data, obs_data_t *settings)
{
	struct color_source *context = data;
	uint32_t color = (uint32_t)obs_data_get_int(settings, "color");
	uint32_t width = (uint32_t)obs_data_get_int(settings, "width");
	uint32_t height = (uint32_t)obs_data_get_int(settings, "height");

	context->color = color;
	context->width = width;
	context->height = height;
}