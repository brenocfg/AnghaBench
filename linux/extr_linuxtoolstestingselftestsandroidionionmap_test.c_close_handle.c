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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_gem_close {int /*<<< orphan*/  handle; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_IOCTL_GEM_CLOSE ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,struct drm_gem_close*) ; 

void close_handle(int vgem_fd, uint32_t handle)
{
	struct drm_gem_close close = { 0 };

	close.handle = handle;
	ioctl(vgem_fd, DRM_IOCTL_GEM_CLOSE, &close);
}