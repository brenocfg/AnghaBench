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
struct vdp_functions {int /*<<< orphan*/  (* video_surface_create ) (int /*<<< orphan*/ ,scalar_t__,int,int,scalar_t__*) ;int /*<<< orphan*/  (* output_surface_create ) (int /*<<< orphan*/ ,scalar_t__,int,int,scalar_t__*) ;int /*<<< orphan*/  (* video_surface_destroy ) (scalar_t__) ;int /*<<< orphan*/  (* output_surface_destroy ) (scalar_t__) ;} ;
struct surface_entry {int allocated; int w; int h; int rgb; scalar_t__ chroma; scalar_t__ rgb_format; scalar_t__ osurface; scalar_t__ surface; scalar_t__ age; int /*<<< orphan*/  in_use; } ;
struct mp_vdpau_ctx {int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  vdp_device; struct surface_entry* video_surfaces; struct vdp_functions vdp; } ;
struct mp_image {int dummy; } ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  scalar_t__ VdpRGBAFormat ;
typedef  scalar_t__ VdpChromaType ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VDP_WARNING (struct mp_vdpau_ctx*,char*) ; 
 int MAX_VIDEO_SURFACES ; 
 int /*<<< orphan*/  MP_ERR (struct mp_vdpau_ctx*,char*) ; 
 scalar_t__ VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 struct mp_image* create_ref (struct mp_vdpau_ctx*,int) ; 
 scalar_t__ mp_vdpau_handle_preemption (struct mp_vdpau_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,scalar_t__,int,int,scalar_t__*) ; 

__attribute__((used)) static struct mp_image *mp_vdpau_get_surface(struct mp_vdpau_ctx *ctx,
                                             VdpChromaType chroma,
                                             VdpRGBAFormat rgb_format,
                                             bool rgb, int w, int h)
{
    struct vdp_functions *vdp = &ctx->vdp;
    int surface_index = -1;
    VdpStatus vdp_st;

    if (rgb) {
        chroma = (VdpChromaType)-1;
    } else {
        rgb_format = (VdpChromaType)-1;
    }

    pthread_mutex_lock(&ctx->pool_lock);

    // Destroy all unused surfaces that don't have matching parameters
    for (int n = 0; n < MAX_VIDEO_SURFACES; n++) {
        struct surface_entry *e = &ctx->video_surfaces[n];
        if (!e->in_use && e->allocated) {
            if (e->w != w || e->h != h || e->rgb != rgb ||
                e->chroma != chroma || e->rgb_format != rgb_format)
            {
                if (e->rgb) {
                    vdp_st = vdp->output_surface_destroy(e->osurface);
                } else {
                    vdp_st = vdp->video_surface_destroy(e->surface);
                }
                CHECK_VDP_WARNING(ctx, "Error when destroying surface");
                e->surface = e->osurface = VDP_INVALID_HANDLE;
                e->allocated = false;
            }
        }
    }

    // Try to find an existing unused surface
    for (int n = 0; n < MAX_VIDEO_SURFACES; n++) {
        struct surface_entry *e = &ctx->video_surfaces[n];
        if (!e->in_use && e->allocated) {
            assert(e->w == w && e->h == h);
            assert(e->chroma == chroma);
            assert(e->rgb_format == rgb_format);
            assert(e->rgb == rgb);
            if (surface_index >= 0) {
                struct surface_entry *other = &ctx->video_surfaces[surface_index];
                if (other->age < e->age)
                    continue;
            }
            surface_index = n;
        }
    }

    if (surface_index >= 0)
        goto done;

    // Allocate new surface
    for (int n = 0; n < MAX_VIDEO_SURFACES; n++) {
        struct surface_entry *e = &ctx->video_surfaces[n];
        if (!e->in_use) {
            assert(e->surface == VDP_INVALID_HANDLE);
            assert(e->osurface == VDP_INVALID_HANDLE);
            assert(!e->allocated);
            e->chroma = chroma;
            e->rgb_format = rgb_format;
            e->rgb = rgb;
            e->w = w;
            e->h = h;
            if (mp_vdpau_handle_preemption(ctx, NULL) >= 0) {
                if (rgb) {
                    vdp_st = vdp->output_surface_create(ctx->vdp_device, rgb_format,
                                                        w, h, &e->osurface);
                    e->allocated = e->osurface != VDP_INVALID_HANDLE;
                } else {
                    vdp_st = vdp->video_surface_create(ctx->vdp_device, chroma,
                                                    w, h, &e->surface);
                    e->allocated = e->surface != VDP_INVALID_HANDLE;
                }
                CHECK_VDP_WARNING(ctx, "Error when allocating surface");
            } else {
                e->allocated = false;
                e->osurface = VDP_INVALID_HANDLE;
                e->surface = VDP_INVALID_HANDLE;
            }
            surface_index = n;
            goto done;
        }
    }

done: ;
    struct mp_image *mpi = NULL;
    if (surface_index >= 0)
        mpi = create_ref(ctx, surface_index);

    pthread_mutex_unlock(&ctx->pool_lock);

    if (!mpi)
        MP_ERR(ctx, "no surfaces available in mp_vdpau_get_video_surface\n");
    return mpi;
}