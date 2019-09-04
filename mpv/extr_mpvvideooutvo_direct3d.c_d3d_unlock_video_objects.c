#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pBits; } ;
struct TYPE_7__ {int /*<<< orphan*/  system; } ;
struct texplane {TYPE_2__ locked_rect; TYPE_1__ texture; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pBits; } ;
struct TYPE_10__ {int plane_count; struct texplane* planes; TYPE_3__ locked_rect; int /*<<< orphan*/  d3d_surface; } ;
typedef  TYPE_4__ d3d_priv ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DSurface9_UnlockRect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DTexture9_UnlockRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_4__*,char*) ; 

__attribute__((used)) static void d3d_unlock_video_objects(d3d_priv *priv)
{
    bool any_failed = false;

    if (priv->locked_rect.pBits) {
        if (FAILED(IDirect3DSurface9_UnlockRect(priv->d3d_surface)))
            any_failed = true;
    }
    priv->locked_rect.pBits = NULL;

    for (int n = 0; n < priv->plane_count; n++) {
        struct texplane *plane = &priv->planes[n];
        if (plane->locked_rect.pBits) {
            if (FAILED(IDirect3DTexture9_UnlockRect(plane->texture.system, 0)))
                any_failed = true;
        }
        plane->locked_rect.pBits = NULL;
    }

    if (any_failed) {
        MP_VERBOSE(priv, "Unlocking video objects failed.\n");
    }
}