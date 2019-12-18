#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct d3drm_frame {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  TYPE_1__ IDirect3DRMFrame3 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  d3drm_frame3_vtbl ; 
 struct d3drm_frame* impl_from_IDirect3DRMFrame3 (TYPE_1__*) ; 

struct d3drm_frame *unsafe_impl_from_IDirect3DRMFrame3(IDirect3DRMFrame3 *iface)
{
    if (!iface)
        return NULL;
    assert(iface->lpVtbl == &d3drm_frame3_vtbl);

    return impl_from_IDirect3DRMFrame3(iface);
}