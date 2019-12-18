#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; scalar_t__ format; } ;
struct gs_texture_2d {scalar_t__ width; scalar_t__ height; TYPE_1__ base; } ;
struct gs_stage_surface {scalar_t__ format; scalar_t__ width; scalar_t__ height; } ;

/* Variables and functions */
 scalar_t__ GS_TEXTURE_2D ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool can_stage(struct gs_stage_surface *dst, struct gs_texture_2d *src)
{
	if (!src) {
		blog(LOG_ERROR, "Source texture is NULL");
		return false;
	}

	if (src->base.type != GS_TEXTURE_2D) {
		blog(LOG_ERROR, "Source texture must be a 2D texture");
		return false;
	}

	if (!dst) {
		blog(LOG_ERROR, "Destination surface is NULL");
		return false;
	}

	if (src->base.format != dst->format) {
		blog(LOG_ERROR, "Source and destination formats do not match");
		return false;
	}

	if (src->width != dst->width || src->height != dst->height) {
		blog(LOG_ERROR, "Source and destination must have the same "
				"dimensions");
		return false;
	}

	return true;
}