#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pBits; } ;
struct TYPE_7__ {int /*<<< orphan*/  system; } ;
struct texplane {TYPE_6__ locked_rect; TYPE_1__ texture; } ;
struct TYPE_8__ {int plane_count; struct texplane* planes; } ;
typedef  TYPE_2__ d3d_priv ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DTexture9_LockRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  d3d_unlock_video_objects (TYPE_2__*) ; 

__attribute__((used)) static bool d3d_lock_video_textures(d3d_priv *priv)
{
    for (int n = 0; n < priv->plane_count; n++) {
        struct texplane *plane = &priv->planes[n];

        if (!plane->locked_rect.pBits) {
            if (FAILED(IDirect3DTexture9_LockRect(plane->texture.system, 0,
                                                  &plane->locked_rect, NULL, 0)))
            {
                MP_VERBOSE(priv, "Texture lock failure.\n");
                d3d_unlock_video_objects(priv);
                return false;
            }
        }
    }

    return true;
}