#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  null; int /*<<< orphan*/  texture; int /*<<< orphan*/  atlas; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int Pitch; scalar_t__ pBits; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ D3DLOCKED_RECT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DFMT_A8R8G8B8 ; 
 int /*<<< orphan*/  D3DPOOL_DEFAULT ; 
 int /*<<< orphan*/  D3DUSAGE_DYNAMIC ; 
 int /*<<< orphan*/  IDirect3DDevice9_CreateTexture (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DTexture9_LockRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DTexture9_UnlockRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NK_FONT_ATLAS_RGBA32 ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 TYPE_2__ d3d9 ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 void* nk_font_atlas_bake (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_font_atlas_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_handle_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nk_d3d9_create_font_texture()
{
    int w, h, y;
    const void *image;

    HRESULT hr;
    D3DLOCKED_RECT locked;

    image = nk_font_atlas_bake(&d3d9.atlas, &w, &h, NK_FONT_ATLAS_RGBA32);

    hr = IDirect3DDevice9_CreateTexture(d3d9.device, w, h, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &d3d9.texture, NULL);
    NK_ASSERT(SUCCEEDED(hr));

    hr = IDirect3DTexture9_LockRect(d3d9.texture, 0, &locked, NULL, 0);
    NK_ASSERT(SUCCEEDED(hr));

    for (y = 0; y < h; y++) {
        void *src = (char *)image + y * w * 4;
        void *dst = (char *)locked.pBits + y * locked.Pitch;
        memcpy(dst, src, w * 4);
    }

    hr = IDirect3DTexture9_UnlockRect(d3d9.texture, 0);
    NK_ASSERT(SUCCEEDED(hr));

    nk_font_atlas_end(&d3d9.atlas, nk_handle_ptr(d3d9.texture), &d3d9.null);
}