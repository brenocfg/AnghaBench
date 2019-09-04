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
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vbox_framebuffer_dirty_rectangles (struct drm_framebuffer*,struct drm_clip_rect*,unsigned int) ; 

__attribute__((used)) static int vbox_user_framebuffer_dirty(struct drm_framebuffer *fb,
				       struct drm_file *file_priv,
				       unsigned int flags, unsigned int color,
				       struct drm_clip_rect *rects,
				       unsigned int num_rects)
{
	vbox_framebuffer_dirty_rectangles(fb, rects, num_rects);

	return 0;
}