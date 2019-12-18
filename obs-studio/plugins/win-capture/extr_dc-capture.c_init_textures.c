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
struct dc_capture {int valid; int /*<<< orphan*/  texture; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ compatibility; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BGRA ; 
 int /*<<< orphan*/  GS_DYNAMIC ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gs_texture_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_create_gdi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void init_textures(struct dc_capture *capture)
{
	if (capture->compatibility)
		capture->texture = gs_texture_create(capture->width,
						     capture->height, GS_BGRA,
						     1, NULL, GS_DYNAMIC);
	else
		capture->texture =
			gs_texture_create_gdi(capture->width, capture->height);

	if (!capture->texture) {
		blog(LOG_WARNING, "[dc_capture_init] Failed to "
				  "create textures");
		return;
	}

	capture->valid = true;
}