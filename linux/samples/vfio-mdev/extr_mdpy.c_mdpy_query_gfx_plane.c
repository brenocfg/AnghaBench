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
struct vfio_device_gfx_plane_info {int flags; int width; int stride; scalar_t__ y_hot; scalar_t__ x_hot; scalar_t__ y_pos; scalar_t__ x_pos; scalar_t__ drm_format_mod; int /*<<< orphan*/  region_index; int /*<<< orphan*/  size; int /*<<< orphan*/  height; int /*<<< orphan*/  drm_format; } ;
struct mdev_state {int /*<<< orphan*/  memsize; TYPE_1__* type; } ;
struct mdev_device {int dummy; } ;
struct TYPE_2__ {int width; int bytepp; int /*<<< orphan*/  height; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MDPY_DISPLAY_REGION ; 
 int VFIO_GFX_PLANE_TYPE_PROBE ; 
 int VFIO_GFX_PLANE_TYPE_REGION ; 
 struct mdev_state* mdev_get_drvdata (struct mdev_device*) ; 

__attribute__((used)) static int mdpy_query_gfx_plane(struct mdev_device *mdev,
				struct vfio_device_gfx_plane_info *plane)
{
	struct mdev_state *mdev_state = mdev_get_drvdata(mdev);

	if (plane->flags & VFIO_GFX_PLANE_TYPE_PROBE) {
		if (plane->flags == (VFIO_GFX_PLANE_TYPE_PROBE |
				     VFIO_GFX_PLANE_TYPE_REGION))
			return 0;
		return -EINVAL;
	}

	if (plane->flags != VFIO_GFX_PLANE_TYPE_REGION)
		return -EINVAL;

	plane->drm_format     = mdev_state->type->format;
	plane->width	      = mdev_state->type->width;
	plane->height	      = mdev_state->type->height;
	plane->stride	      = (mdev_state->type->width *
				 mdev_state->type->bytepp);
	plane->size	      = mdev_state->memsize;
	plane->region_index   = MDPY_DISPLAY_REGION;

	/* unused */
	plane->drm_format_mod = 0;
	plane->x_pos	      = 0;
	plane->y_pos	      = 0;
	plane->x_hot	      = 0;
	plane->y_hot	      = 0;

	return 0;
}