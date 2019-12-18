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
struct d3d9 {int refcount; scalar_t__ extended; int /*<<< orphan*/  wined3d; TYPE_1__ IDirect3D9Ex_iface; } ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int WINED3D_HANDLE_RESTORE ; 
 int WINED3D_LEGACY_CUBEMAP_FILTERING ; 
 int WINED3D_LEGACY_UNBOUND_RESOURCE_COLOR ; 
 int WINED3D_LIMIT_VIEWPORT ; 
 int WINED3D_NORMALIZED_DEPTH_BIAS ; 
 int WINED3D_NO_PRIMITIVE_RESTART ; 
 int WINED3D_PIXEL_CENTER_INTEGER ; 
 int WINED3D_PRESENT_CONVERSION ; 
 int WINED3D_RESTORE_MODE_ON_ACTIVATE ; 
 int WINED3D_SRGB_READ_WRITE_CONTROL ; 
 int WINED3D_VIDMEM_ACCOUNTING ; 
 int /*<<< orphan*/  d3d9_vtbl ; 
 int /*<<< orphan*/  wined3d_create (int) ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 

BOOL d3d9_init(struct d3d9 *d3d9, BOOL extended)
{
    DWORD flags = WINED3D_PRESENT_CONVERSION | WINED3D_HANDLE_RESTORE | WINED3D_PIXEL_CENTER_INTEGER
            | WINED3D_SRGB_READ_WRITE_CONTROL | WINED3D_LEGACY_UNBOUND_RESOURCE_COLOR
            | WINED3D_NO_PRIMITIVE_RESTART | WINED3D_LEGACY_CUBEMAP_FILTERING
            | WINED3D_NORMALIZED_DEPTH_BIAS | WINED3D_LIMIT_VIEWPORT;

    if (!extended)
        flags |= WINED3D_VIDMEM_ACCOUNTING;
    else
        flags |= WINED3D_RESTORE_MODE_ON_ACTIVATE;

    d3d9->IDirect3D9Ex_iface.lpVtbl = &d3d9_vtbl;
    d3d9->refcount = 1;

    wined3d_mutex_lock();
    d3d9->wined3d = wined3d_create(flags);
    wined3d_mutex_unlock();
    if (!d3d9->wined3d)
        return FALSE;
    d3d9->extended = extended;

    return TRUE;
}