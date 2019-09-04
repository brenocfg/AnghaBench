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
struct d3d8_vertexbuffer {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  TYPE_1__ IDirect3DVertexBuffer8 ;

/* Variables and functions */
 int /*<<< orphan*/  Direct3DVertexBuffer8_Vtbl ; 
 int /*<<< orphan*/  assert (int) ; 
 struct d3d8_vertexbuffer* impl_from_IDirect3DVertexBuffer8 (TYPE_1__*) ; 

struct d3d8_vertexbuffer *unsafe_impl_from_IDirect3DVertexBuffer8(IDirect3DVertexBuffer8 *iface)
{
    if (!iface)
        return NULL;
    assert(iface->lpVtbl == &Direct3DVertexBuffer8_Vtbl);

    return impl_from_IDirect3DVertexBuffer8(iface);
}