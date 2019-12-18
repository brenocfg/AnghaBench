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
struct mp_log {int dummy; } ;
struct drm_prime_framebuffer {scalar_t__* gem_handles; scalar_t__ fb_id; } ;

/* Variables and functions */
 int AV_DRM_MAX_PLANES ; 
 int /*<<< orphan*/  DRM_IOCTL_GEM_CLOSE ; 
 int /*<<< orphan*/  drmIoctl (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  drmModeRmFB (int,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct drm_prime_framebuffer*,int /*<<< orphan*/ ,int) ; 

void drm_prime_destroy_framebuffer(struct mp_log *log, int fd, struct  drm_prime_framebuffer *framebuffer)
{
    if (framebuffer->fb_id)
        drmModeRmFB(fd, framebuffer->fb_id);

    for (int i = 0; i < AV_DRM_MAX_PLANES; i++) {
        if (framebuffer->gem_handles[i])
            drmIoctl(fd, DRM_IOCTL_GEM_CLOSE, &framebuffer->gem_handles[i]);
    }

    memset(framebuffer, 0, sizeof(*framebuffer));
}