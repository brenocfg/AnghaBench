#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ cur_backbuf_width; scalar_t__ cur_backbuf_height; TYPE_1__* vo; int /*<<< orphan*/  d3d_device; int /*<<< orphan*/  image_format; scalar_t__ opt_exact_backbuffer; } ;
typedef  TYPE_2__ d3d_priv ;
struct TYPE_14__ {scalar_t__ member_2; scalar_t__ member_3; int member_5; scalar_t__ Height; scalar_t__ Width; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {scalar_t__ dwidth; scalar_t__ dheight; int want_redraw; } ;
typedef  TYPE_3__ D3DVIEWPORT9 ;
typedef  int /*<<< orphan*/  D3DMATRIX ;

/* Variables and functions */
 int /*<<< orphan*/  D3DTS_VIEW ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetViewport (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  calc_fs_rect (TYPE_2__*) ; 
 int /*<<< orphan*/  change_d3d_backbuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  create_d3d_surfaces (TYPE_2__*) ; 
 int /*<<< orphan*/  d3d_matrix_ortho (int /*<<< orphan*/ *,float,scalar_t__,scalar_t__,float) ; 
 int /*<<< orphan*/  destroy_d3d_surfaces (TYPE_2__*) ; 

__attribute__((used)) static bool resize_d3d(d3d_priv *priv)
{
    D3DVIEWPORT9 vp = {0, 0, priv->vo->dwidth, priv->vo->dheight, 0, 1};

    MP_VERBOSE(priv, "resize_d3d %dx%d called.\n",
               priv->vo->dwidth, priv->vo->dheight);

    /* Make sure that backbuffer is large enough to accommodate the new
       viewport dimensions. Grow it if necessary. */

    bool backbuf_resize = priv->vo->dwidth > priv->cur_backbuf_width ||
                          priv->vo->dheight > priv->cur_backbuf_height;

    if (priv->opt_exact_backbuffer) {
        backbuf_resize = priv->vo->dwidth != priv->cur_backbuf_width ||
                         priv->vo->dheight != priv->cur_backbuf_height;
    }

    if (backbuf_resize || !priv->d3d_device)
    {
        destroy_d3d_surfaces(priv);
        if (!change_d3d_backbuffer(priv))
            return 0;
    }

    if (!priv->d3d_device || !priv->image_format)
        return 1;

    if (!create_d3d_surfaces(priv))
        return 0;

    if (FAILED(IDirect3DDevice9_SetViewport(priv->d3d_device, &vp))) {
        MP_ERR(priv, "Setting viewport failed.\n");
        return 0;
    }

    // so that screen coordinates map to D3D ones
    D3DMATRIX view;
    d3d_matrix_ortho(&view, 0.5f, vp.Width + 0.5f, vp.Height + 0.5f, 0.5f);
    IDirect3DDevice9_SetTransform(priv->d3d_device, D3DTS_VIEW, &view);

    calc_fs_rect(priv);
    priv->vo->want_redraw = true;

    return 1;
}