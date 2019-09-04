#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int plane_count; TYPE_1__* planes; int /*<<< orphan*/ * d3d_surface; } ;
typedef  TYPE_2__ d3d_priv ;
struct TYPE_6__ {int /*<<< orphan*/  texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DSurface9_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d_unlock_video_objects (TYPE_2__*) ; 
 int /*<<< orphan*/  d3dtex_release (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d3d_destroy_video_objects(d3d_priv *priv)
{
    d3d_unlock_video_objects(priv);

    if (priv->d3d_surface)
        IDirect3DSurface9_Release(priv->d3d_surface);
    priv->d3d_surface = NULL;

    for (int n = 0; n < priv->plane_count; n++) {
        d3dtex_release(priv, &priv->planes[n].texture);
    }
}