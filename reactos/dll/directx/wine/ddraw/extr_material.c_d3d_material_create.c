#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ddraw {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3d_material {int ref; struct ddraw* ddraw; TYPE_3__ IDirect3DMaterial_iface; TYPE_2__ IDirect3DMaterial2_iface; TYPE_1__ IDirect3DMaterial3_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3d_material1_vtbl ; 
 int /*<<< orphan*/  d3d_material2_vtbl ; 
 int /*<<< orphan*/  d3d_material3_vtbl ; 
 struct d3d_material* heap_alloc_zero (int) ; 

struct d3d_material *d3d_material_create(struct ddraw *ddraw)
{
    struct d3d_material *material;

    if (!(material = heap_alloc_zero(sizeof(*material))))
        return NULL;

    material->IDirect3DMaterial3_iface.lpVtbl = &d3d_material3_vtbl;
    material->IDirect3DMaterial2_iface.lpVtbl = &d3d_material2_vtbl;
    material->IDirect3DMaterial_iface.lpVtbl = &d3d_material1_vtbl;
    material->ref = 1;
    material->ddraw = ddraw;

    return material;
}