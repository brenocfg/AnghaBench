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
struct d3dtex {int w; int h; int tex_w; int tex_h; int /*<<< orphan*/  device; int /*<<< orphan*/  system; } ;
struct TYPE_6__ {int opt_texture_memory; int /*<<< orphan*/  d3d_device; int /*<<< orphan*/  device_texture_sys; } ;
typedef  TYPE_1__ d3d_priv ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 int D3DPOOL_DEFAULT ; 
 int D3DPOOL_MANAGED ; 
 int D3DPOOL_SCRATCH ; 
 int D3DPOOL_SYSTEMMEM ; 
 int /*<<< orphan*/  D3DUSAGE_DYNAMIC ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_CreateTexture (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  d3d_fix_texture_size (TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  d3dtex_release (TYPE_1__*,struct d3dtex*) ; 

__attribute__((used)) static bool d3dtex_allocate(d3d_priv *priv, struct d3dtex *tex, D3DFORMAT fmt,
                            int w, int h)
{
    d3dtex_release(priv, tex);

    tex->w = w;
    tex->h = h;

    int tw = w, th = h;
    d3d_fix_texture_size(priv, &tw, &th);

    bool use_sh = !priv->device_texture_sys;
    int memtype = D3DPOOL_SYSTEMMEM;
    switch (priv->opt_texture_memory) {
    case 1: memtype = D3DPOOL_MANAGED; use_sh = false; break;
    case 2: memtype = D3DPOOL_DEFAULT; use_sh = false; break;
    case 3: memtype = D3DPOOL_DEFAULT; use_sh = true; break;
    case 4: memtype = D3DPOOL_SCRATCH; use_sh = true; break;
    }

    if (FAILED(IDirect3DDevice9_CreateTexture(priv->d3d_device, tw, th, 1,
        D3DUSAGE_DYNAMIC, fmt, memtype, &tex->system, NULL)))
    {
        MP_ERR(priv, "Allocating %dx%d texture in system RAM failed.\n", w, h);
        goto error_exit;
    }

    if (use_sh) {
        if (FAILED(IDirect3DDevice9_CreateTexture(priv->d3d_device, tw, th, 1,
            D3DUSAGE_DYNAMIC, fmt, D3DPOOL_DEFAULT, &tex->device, NULL)))
        {
            MP_ERR(priv, "Allocating %dx%d texture in video RAM failed.\n", w, h);
            goto error_exit;
        }
    }

    tex->tex_w = tw;
    tex->tex_h = th;

    return true;

error_exit:
    d3dtex_release(priv, tex);
    return false;
}