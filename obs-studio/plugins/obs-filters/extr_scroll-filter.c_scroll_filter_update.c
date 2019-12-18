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
typedef  void* uint32_t ;
struct TYPE_4__ {float x; float y; } ;
struct TYPE_3__ {float x; float y; } ;
struct scroll_filter_data {TYPE_2__ offset; TYPE_1__ scroll_speed; int /*<<< orphan*/  sampler; void* loop; void* cy; void* cx; void* limit_cy; void* limit_cx; } ;
struct gs_sampler_info {int /*<<< orphan*/  address_v; int /*<<< orphan*/  address_u; int /*<<< orphan*/  filter; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_ADDRESS_BORDER ; 
 int /*<<< orphan*/  GS_ADDRESS_WRAP ; 
 int /*<<< orphan*/  GS_FILTER_LINEAR ; 
 int /*<<< orphan*/  gs_samplerstate_create (struct gs_sampler_info*) ; 
 int /*<<< orphan*/  gs_samplerstate_destroy (int /*<<< orphan*/ ) ; 
 void* obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_double (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void scroll_filter_update(void *data, obs_data_t *settings)
{
	struct scroll_filter_data *filter = data;

	filter->limit_cx = obs_data_get_bool(settings, "limit_cx");
	filter->limit_cy = obs_data_get_bool(settings, "limit_cy");
	filter->cx = (uint32_t)obs_data_get_int(settings, "cx");
	filter->cy = (uint32_t)obs_data_get_int(settings, "cy");

	filter->scroll_speed.x =
		(float)obs_data_get_double(settings, "speed_x");
	filter->scroll_speed.y =
		(float)obs_data_get_double(settings, "speed_y");

	filter->loop = obs_data_get_bool(settings, "loop");

	struct gs_sampler_info sampler_info = {
		.filter = GS_FILTER_LINEAR,
		.address_u = filter->loop ? GS_ADDRESS_WRAP : GS_ADDRESS_BORDER,
		.address_v = filter->loop ? GS_ADDRESS_WRAP : GS_ADDRESS_BORDER,
	};

	obs_enter_graphics();
	gs_samplerstate_destroy(filter->sampler);
	filter->sampler = gs_samplerstate_create(&sampler_info);
	obs_leave_graphics();

	if (filter->scroll_speed.x == 0.0f)
		filter->offset.x = 0.0f;
	if (filter->scroll_speed.y == 0.0f)
		filter->offset.y = 0.0f;
}