#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dwHeight; int /*<<< orphan*/  dwWidth; } ;
struct ddraw_surface {int /*<<< orphan*/  sub_resource_idx; int /*<<< orphan*/  wined3d_texture; TYPE_2__* palette; TYPE_1__ surface_desc; struct ddraw* ddraw; } ;
struct ddraw {int flags; int /*<<< orphan*/  wined3d_frontbuffer; scalar_t__ swapchain_window; } ;
struct TYPE_10__ {int left; int top; int right; int bottom; } ;
struct TYPE_9__ {int /*<<< orphan*/  wined3d_palette; } ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ BitBlt (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int DDRAW_GDI_FLIP ; 
 int /*<<< orphan*/  DD_OK ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SetRect (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3D_TEXF_POINT ; 
 int /*<<< orphan*/  wined3d_palette_apply_to_dc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_blt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_dc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_texture_release_dc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HRESULT ddraw_surface_update_frontbuffer(struct ddraw_surface *surface, const RECT *rect, BOOL read)
{
    struct ddraw *ddraw = surface->ddraw;
    HDC surface_dc, screen_dc;
    int x, y, w, h;
    HRESULT hr;
    BOOL ret;
    RECT r;

    if (!rect)
    {
        SetRect(&r, 0, 0, surface->surface_desc.dwWidth, surface->surface_desc.dwHeight);
        rect = &r;
    }

    x = rect->left;
    y = rect->top;
    w = rect->right - rect->left;
    h = rect->bottom - rect->top;

    if (w <= 0 || h <= 0)
        return DD_OK;

    if (ddraw->swapchain_window && !(ddraw->flags & DDRAW_GDI_FLIP))
    {
        /* Nothing to do, we control the frontbuffer, or at least the parts we
         * care about. */
        if (read)
            return DD_OK;

        return wined3d_texture_blt(ddraw->wined3d_frontbuffer, 0, rect,
                surface->wined3d_texture, surface->sub_resource_idx, rect, 0, NULL, WINED3D_TEXF_POINT);
    }

    if (FAILED(hr = wined3d_texture_get_dc(surface->wined3d_texture, surface->sub_resource_idx, &surface_dc)))
    {
        ERR("Failed to get surface DC, hr %#x.\n", hr);
        return hr;
    }
    if (surface->palette)
        wined3d_palette_apply_to_dc(surface->palette->wined3d_palette, surface_dc);

    if (!(screen_dc = GetDC(NULL)))
    {
        wined3d_texture_release_dc(surface->wined3d_texture, surface->sub_resource_idx, surface_dc);
        ERR("Failed to get screen DC.\n");
        return E_FAIL;
    }

    if (read)
        ret = BitBlt(surface_dc, x, y, w, h,
                screen_dc, x, y, SRCCOPY);
    else
        ret = BitBlt(screen_dc, x, y, w, h,
                surface_dc, x, y, SRCCOPY);

    ReleaseDC(NULL, screen_dc);
    wined3d_texture_release_dc(surface->wined3d_texture, surface->sub_resource_idx, surface_dc);

    if (!ret)
    {
        ERR("Failed to blit to/from screen.\n");
        return E_FAIL;
    }

    return DD_OK;
}