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
struct mp_vdpau_ctx {int dummy; } ;
struct mp_image {int dummy; } ;
typedef  int /*<<< orphan*/  VdpChromaType ;

/* Variables and functions */
 struct mp_image* mp_vdpau_get_surface (struct mp_vdpau_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

struct mp_image *mp_vdpau_get_video_surface(struct mp_vdpau_ctx *ctx,
                                            VdpChromaType chroma, int w, int h)
{
    return mp_vdpau_get_surface(ctx, chroma, 0, false, w, h);
}