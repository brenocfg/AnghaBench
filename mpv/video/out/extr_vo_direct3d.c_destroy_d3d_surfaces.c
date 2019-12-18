#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct osdpart {int change_id; int /*<<< orphan*/  texture; } ;
struct TYPE_6__ {int d3d_in_scene; int /*<<< orphan*/ * d3d_backbuf; struct osdpart** osd; } ;
typedef  TYPE_1__ d3d_priv ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DSurface9_Release (int /*<<< orphan*/ *) ; 
 int MAX_OSD_PARTS ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  d3d_destroy_video_objects (TYPE_1__*) ; 
 int /*<<< orphan*/  d3dtex_release (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_d3d_surfaces(d3d_priv *priv)
{
    MP_VERBOSE(priv, "destroy_d3d_surfaces called.\n");

    d3d_destroy_video_objects(priv);

    for (int n = 0; n < MAX_OSD_PARTS; n++) {
        struct osdpart *osd = priv->osd[n];
        d3dtex_release(priv, &osd->texture);
        osd->change_id = -1;
    }

    if (priv->d3d_backbuf)
        IDirect3DSurface9_Release(priv->d3d_backbuf);
    priv->d3d_backbuf = NULL;

    priv->d3d_in_scene = false;
}