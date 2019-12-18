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
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  depth; } ;
struct framebuffer {int /*<<< orphan*/  size; int /*<<< orphan*/  map; int /*<<< orphan*/  handle; int /*<<< orphan*/  fb; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_mode_map_dumb {int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; int /*<<< orphan*/  bpp; int /*<<< orphan*/  size; int /*<<< orphan*/  pitch; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_mode_create_dumb {int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; int /*<<< orphan*/  bpp; int /*<<< orphan*/  size; int /*<<< orphan*/  pitch; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_PIXEL ; 
 int /*<<< orphan*/  DRM_IOCTL_MODE_CREATE_DUMB ; 
 int /*<<< orphan*/  DRM_IOCTL_MODE_MAP_DUMB ; 
 int /*<<< orphan*/  MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MP_ERR (struct vo*,char*,int /*<<< orphan*/ ) ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ drmIoctl (int,int /*<<< orphan*/ ,struct drm_mode_map_dumb*) ; 
 scalar_t__ drmModeAddFB (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fb_destroy (int,struct framebuffer*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fb_setup_single(struct vo *vo, int fd, struct framebuffer *buf)
{
    struct priv *p = vo->priv;

    buf->handle = 0;

    // create dumb buffer
    struct drm_mode_create_dumb creq = {
        .width = buf->width,
        .height = buf->height,
        .bpp = BITS_PER_PIXEL,
    };
    if (drmIoctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &creq) < 0) {
        MP_ERR(vo, "Cannot create dumb buffer: %s\n", mp_strerror(errno));
        goto err;
    }
    buf->stride = creq.pitch;
    buf->size = creq.size;
    buf->handle = creq.handle;

    // create framebuffer object for the dumb-buffer
    if (drmModeAddFB(fd, buf->width, buf->height, p->depth, creq.bpp, buf->stride,
                     buf->handle, &buf->fb)) {
        MP_ERR(vo, "Cannot create framebuffer: %s\n", mp_strerror(errno));
        goto err;
    }

    // prepare buffer for memory mapping
    struct drm_mode_map_dumb mreq = {
        .handle = buf->handle,
    };
    if (drmIoctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &mreq)) {
        MP_ERR(vo, "Cannot map dumb buffer: %s\n", mp_strerror(errno));
        goto err;
    }

    // perform actual memory mapping
    buf->map = mmap(0, buf->size, PROT_READ | PROT_WRITE, MAP_SHARED,
                    fd, mreq.offset);
    if (buf->map == MAP_FAILED) {
        MP_ERR(vo, "Cannot map dumb buffer: %s\n", mp_strerror(errno));
        goto err;
    }

    memset(buf->map, 0, buf->size);
    return true;

err:
    fb_destroy(fd, buf);
    return false;
}