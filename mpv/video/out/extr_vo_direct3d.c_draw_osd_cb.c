#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vertex_osd ;
struct sub_bitmaps {scalar_t__ format; } ;
struct osdpart {int num_vertices; int /*<<< orphan*/  vertices; int /*<<< orphan*/  texture; } ;
struct TYPE_5__ {int /*<<< orphan*/  d3d_device; } ;
typedef  TYPE_1__ d3d_priv ;

/* Variables and functions */
 int D3DBLEND_ONE ; 
 int D3DBLEND_SRCALPHA ; 
 int /*<<< orphan*/  D3DFVF_OSD_VERTEX ; 
 int /*<<< orphan*/  D3DPT_TRIANGLELIST ; 
 int /*<<< orphan*/  D3DRS_ALPHABLENDENABLE ; 
 int /*<<< orphan*/  D3DRS_SRCBLEND ; 
 int /*<<< orphan*/  D3DRS_TEXTUREFACTOR ; 
 int /*<<< orphan*/  D3DTA_TEXTURE ; 
 int /*<<< orphan*/  D3DTA_TFACTOR ; 
 int /*<<< orphan*/  D3DTOP_MODULATE ; 
 int /*<<< orphan*/  D3DTOP_SELECTARG1 ; 
 int /*<<< orphan*/  D3DTSS_ALPHAOP ; 
 int /*<<< orphan*/  D3DTSS_COLORARG1 ; 
 int FALSE ; 
 int /*<<< orphan*/  IDirect3DDevice9_DrawPrimitiveUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetFVF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetRenderState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetTextureStageState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SUBBITMAP_LIBASS ; 
 int TRUE ; 
 int /*<<< orphan*/  d3d_begin_scene (TYPE_1__*) ; 
 int /*<<< orphan*/ * d3dtex_get_render_texture (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct osdpart* generate_osd (TYPE_1__*,struct sub_bitmaps*) ; 

__attribute__((used)) static void draw_osd_cb(void *ctx, struct sub_bitmaps *imgs)
{
    d3d_priv *priv = ctx;

    struct osdpart *osd = generate_osd(priv, imgs);
    if (!osd)
        return;

    d3d_begin_scene(priv);

    IDirect3DDevice9_SetRenderState(priv->d3d_device,
                                    D3DRS_ALPHABLENDENABLE, TRUE);

    IDirect3DDevice9_SetTexture(priv->d3d_device, 0,
                                d3dtex_get_render_texture(priv, &osd->texture));

    if (imgs->format == SUBBITMAP_LIBASS) {
        // do not use the color value from the A8 texture, because that is black
        IDirect3DDevice9_SetRenderState(priv->d3d_device,D3DRS_TEXTUREFACTOR,
                                        0xFFFFFFFF);
        IDirect3DDevice9_SetTextureStageState(priv->d3d_device,0,
                                            D3DTSS_COLORARG1, D3DTA_TFACTOR);

        IDirect3DDevice9_SetTextureStageState(priv->d3d_device, 0,
                                            D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    } else {
        IDirect3DDevice9_SetRenderState(priv->d3d_device, D3DRS_SRCBLEND,
                                        D3DBLEND_ONE);
    }

    IDirect3DDevice9_SetFVF(priv->d3d_device, D3DFVF_OSD_VERTEX);
    IDirect3DDevice9_DrawPrimitiveUP(priv->d3d_device, D3DPT_TRIANGLELIST,
                                     osd->num_vertices / 3,
                                     osd->vertices, sizeof(vertex_osd));

    IDirect3DDevice9_SetTextureStageState(priv->d3d_device,0,
                                          D3DTSS_COLORARG1, D3DTA_TEXTURE);
    IDirect3DDevice9_SetTextureStageState(priv->d3d_device, 0,
                                          D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    IDirect3DDevice9_SetRenderState(priv->d3d_device,
                                    D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

    IDirect3DDevice9_SetTexture(priv->d3d_device, 0, NULL);

    IDirect3DDevice9_SetRenderState(priv->d3d_device,
                                    D3DRS_ALPHABLENDENABLE, FALSE);
}