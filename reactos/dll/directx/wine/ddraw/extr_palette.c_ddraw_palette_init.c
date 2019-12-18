#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct ddraw_palette {int ref; int flags; int /*<<< orphan*/ * ifaceToRelease; struct ddraw* ddraw; int /*<<< orphan*/  wined3d_palette; TYPE_1__ IDirectDrawPalette_iface; } ;
struct ddraw {int /*<<< orphan*/  IDirectDraw7_iface; int /*<<< orphan*/  wined3d_device; } ;
typedef  int /*<<< orphan*/  PALETTEENTRY ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int DDERR_INVALIDPARAMS ; 
 int DDPCAPS_8BITENTRIES ; 
 int DDPCAPS_ALLOW256 ; 
 int DDPCAPS_ALPHA ; 
 int DD_OK ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int WINED3D_PALETTE_8BIT_ENTRIES ; 
 int WINED3D_PALETTE_ALLOW_256 ; 
 int WINED3D_PALETTE_ALPHA ; 
 int /*<<< orphan*/  ddraw_palette_vtbl ; 
 unsigned int palette_size (int) ; 
 int wined3d_palette_create (int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT ddraw_palette_init(struct ddraw_palette *palette,
        struct ddraw *ddraw, DWORD flags, PALETTEENTRY *entries)
{
    unsigned int entry_count;
    DWORD wined3d_flags = 0;
    HRESULT hr;

    if ((entry_count = palette_size(flags)) == ~0u)
    {
        WARN("Invalid flags %#x.\n", flags);
        return DDERR_INVALIDPARAMS;
    }

    if (flags & DDPCAPS_8BITENTRIES)
        wined3d_flags |= WINED3D_PALETTE_8BIT_ENTRIES;
    if (flags & DDPCAPS_ALLOW256)
        wined3d_flags |= WINED3D_PALETTE_ALLOW_256;
    if (flags & DDPCAPS_ALPHA)
        wined3d_flags |= WINED3D_PALETTE_ALPHA;

    palette->IDirectDrawPalette_iface.lpVtbl = &ddraw_palette_vtbl;
    palette->ref = 1;
    palette->flags = flags;

    if (FAILED(hr = wined3d_palette_create(ddraw->wined3d_device,
            wined3d_flags, entry_count, entries, &palette->wined3d_palette)))
    {
        WARN("Failed to create wined3d palette, hr %#x.\n", hr);
        return hr;
    }

    palette->ddraw = ddraw;
    palette->ifaceToRelease = (IUnknown *)&ddraw->IDirectDraw7_iface;
    IUnknown_AddRef(palette->ifaceToRelease);

    return DD_OK;
}