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
struct gs_monitor_info {int /*<<< orphan*/  rotation_degrees; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  member_0; } ;
struct duplicator_capture {int /*<<< orphan*/  rot; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  monitor; int /*<<< orphan*/  duplicator; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/ * gs_duplicator_get_texture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_get_duplicator_monitor_info (int /*<<< orphan*/ ,struct gs_monitor_info*) ; 
 int /*<<< orphan*/  gs_texture_get_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texture_get_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_capture_data(struct duplicator_capture *capture)
{
	struct gs_monitor_info monitor_info = {0};
	gs_texture_t *texture = gs_duplicator_get_texture(capture->duplicator);

	gs_get_duplicator_monitor_info(capture->monitor, &monitor_info);
	capture->width = gs_texture_get_width(texture);
	capture->height = gs_texture_get_height(texture);
	capture->x = monitor_info.x;
	capture->y = monitor_info.y;
	capture->rot = monitor_info.rotation_degrees;
}