#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct d3d9_pixelshader {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  TYPE_1__ IDirect3DPixelShader9 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d9_pixelshader_vtbl ; 
 struct d3d9_pixelshader* impl_from_IDirect3DPixelShader9 (TYPE_1__*) ; 

struct d3d9_pixelshader *unsafe_impl_from_IDirect3DPixelShader9(IDirect3DPixelShader9 *iface)
{
    if (!iface)
        return NULL;
    if (iface->lpVtbl != &d3d9_pixelshader_vtbl)
        WARN("Pixel shader %p with the wrong vtbl %p\n", iface, iface->lpVtbl);

    return impl_from_IDirect3DPixelShader9(iface);
}