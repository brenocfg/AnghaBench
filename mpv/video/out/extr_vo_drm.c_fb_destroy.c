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
struct framebuffer {scalar_t__ handle; scalar_t__ fb; int /*<<< orphan*/  size; scalar_t__ map; } ;
struct drm_mode_destroy_dumb {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_IOCTL_MODE_DESTROY_DUMB ; 
 int /*<<< orphan*/  drmIoctl (int,int /*<<< orphan*/ ,struct drm_mode_destroy_dumb*) ; 
 int /*<<< orphan*/  drmModeRmFB (int,scalar_t__) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fb_destroy(int fd, struct framebuffer *buf)
{
    if (buf->map) {
        munmap(buf->map, buf->size);
    }
    if (buf->fb) {
        drmModeRmFB(fd, buf->fb);
    }
    if (buf->handle) {
        struct drm_mode_destroy_dumb dreq = {
            .handle = buf->handle,
        };
        drmIoctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &dreq);
    }
}