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
struct mp_vdpau_ctx {void* preemption_obj; void* vdp_device; TYPE_1__* video_surfaces; } ;
struct TYPE_2__ {int allocated; void* osurface; void* surface; } ;

/* Variables and functions */
 int MAX_VIDEO_SURFACES ; 
 void* VDP_INVALID_HANDLE ; 

__attribute__((used)) static void mark_vdpau_objects_uninitialized(struct mp_vdpau_ctx *ctx)
{
    for (int i = 0; i < MAX_VIDEO_SURFACES; i++) {
        ctx->video_surfaces[i].surface = VDP_INVALID_HANDLE;
        ctx->video_surfaces[i].osurface = VDP_INVALID_HANDLE;
        ctx->video_surfaces[i].allocated = false;
    }
    ctx->vdp_device = VDP_INVALID_HANDLE;
    ctx->preemption_obj = VDP_INVALID_HANDLE;
}