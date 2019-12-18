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
struct d3d9_vertexbuffer {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  TYPE_1__ IDirect3DVertexBuffer9 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  d3d9_vertexbuffer_vtbl ; 
 struct d3d9_vertexbuffer* impl_from_IDirect3DVertexBuffer9 (TYPE_1__*) ; 

struct d3d9_vertexbuffer *unsafe_impl_from_IDirect3DVertexBuffer9(IDirect3DVertexBuffer9 *iface)
{
    if (!iface)
        return NULL;
    assert(iface->lpVtbl == &d3d9_vertexbuffer_vtbl);

    return impl_from_IDirect3DVertexBuffer9(iface);
}