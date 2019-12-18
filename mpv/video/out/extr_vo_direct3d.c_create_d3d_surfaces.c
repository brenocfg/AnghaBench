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
struct TYPE_6__ {int /*<<< orphan*/  d3d_device; int /*<<< orphan*/  d3d_backbuf; } ;
typedef  TYPE_1__ d3d_priv ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DBACKBUFFER_TYPE_MONO ; 
 int /*<<< orphan*/  D3DBLEND_INVSRCALPHA ; 
 int /*<<< orphan*/  D3DBLEND_SRCALPHA ; 
 int /*<<< orphan*/  D3DCMP_GREATER ; 
 int /*<<< orphan*/  D3DRS_ALPHAFUNC ; 
 int /*<<< orphan*/  D3DRS_ALPHAREF ; 
 int /*<<< orphan*/  D3DRS_DESTBLEND ; 
 int /*<<< orphan*/  D3DRS_LIGHTING ; 
 int /*<<< orphan*/  D3DRS_SRCBLEND ; 
 int /*<<< orphan*/  D3DSAMP_ADDRESSU ; 
 int /*<<< orphan*/  D3DSAMP_ADDRESSV ; 
 int /*<<< orphan*/  D3DSAMP_MAGFILTER ; 
 int /*<<< orphan*/  D3DSAMP_MINFILTER ; 
 int /*<<< orphan*/  D3DTADDRESS_CLAMP ; 
 int /*<<< orphan*/  D3DTEXF_LINEAR ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDirect3DDevice9_GetBackBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetRenderState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetSamplerState (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  d3d_configure_video_objects (TYPE_1__*) ; 

__attribute__((used)) static bool create_d3d_surfaces(d3d_priv *priv)
{
    MP_VERBOSE(priv, "create_d3d_surfaces called.\n");

    if (!priv->d3d_backbuf &&
        FAILED(IDirect3DDevice9_GetBackBuffer(priv->d3d_device, 0, 0,
                                              D3DBACKBUFFER_TYPE_MONO,
                                              &priv->d3d_backbuf))) {
        MP_ERR(priv, "Allocating backbuffer failed.\n");
        return 0;
    }

    if (!d3d_configure_video_objects(priv))
        return 0;

    /* setup default renderstate */
    IDirect3DDevice9_SetRenderState(priv->d3d_device,
                                    D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    IDirect3DDevice9_SetRenderState(priv->d3d_device,
                                    D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    IDirect3DDevice9_SetRenderState(priv->d3d_device,
                                    D3DRS_ALPHAFUNC, D3DCMP_GREATER);
    IDirect3DDevice9_SetRenderState(priv->d3d_device,
                                    D3DRS_ALPHAREF, (DWORD)0x0);
    IDirect3DDevice9_SetRenderState(priv->d3d_device,
                                    D3DRS_LIGHTING, FALSE);

    // we use up to 3 samplers for up to 3 YUV planes
    for (int n = 0; n < 3; n++) {
        IDirect3DDevice9_SetSamplerState(priv->d3d_device, n, D3DSAMP_MINFILTER,
                                         D3DTEXF_LINEAR);
        IDirect3DDevice9_SetSamplerState(priv->d3d_device, n, D3DSAMP_MAGFILTER,
                                         D3DTEXF_LINEAR);
        IDirect3DDevice9_SetSamplerState(priv->d3d_device, n, D3DSAMP_ADDRESSU,
                                         D3DTADDRESS_CLAMP);
        IDirect3DDevice9_SetSamplerState(priv->d3d_device, n, D3DSAMP_ADDRESSV,
                                         D3DTADDRESS_CLAMP);
    }

    return 1;
}