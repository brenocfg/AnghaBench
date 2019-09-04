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
typedef  scalar_t__ uint32_t ;
struct drm_prime_handle {int fd; scalar_t__ handle; scalar_t__ flags; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_IOCTL_PRIME_FD_TO_HANDLE ; 
 int ioctl (int,int /*<<< orphan*/ ,struct drm_prime_handle*) ; 

int import_vgem_fd(int vgem_fd, int dma_buf_fd, uint32_t *handle)
{
	struct drm_prime_handle import_handle = { 0 };
	int ret;

	import_handle.fd = dma_buf_fd;
	import_handle.flags = 0;
	import_handle.handle = 0;

	ret = ioctl(vgem_fd, DRM_IOCTL_PRIME_FD_TO_HANDLE, &import_handle);
	if (ret == 0)
		*handle = import_handle.handle;
	return ret;
}