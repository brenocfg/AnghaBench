#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct d3d8_vertex_declaration {int /*<<< orphan*/  wined3d_vertex_declaration; int /*<<< orphan*/  shader_handle; scalar_t__ elements_size; int /*<<< orphan*/ * elements; } ;
struct d3d8_device {int /*<<< orphan*/  wined3d_device; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_vertexdeclaration_wined3d_parent_ops ; 
 int /*<<< orphan*/  wined3d_vertex_declaration_create_from_fvf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct d3d8_vertex_declaration*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT d3d8_vertex_declaration_init_fvf(struct d3d8_vertex_declaration *declaration,
        struct d3d8_device *device, DWORD fvf)
{
    HRESULT hr;

    declaration->elements = NULL;
    declaration->elements_size = 0;
    declaration->shader_handle = fvf;

    hr = wined3d_vertex_declaration_create_from_fvf(device->wined3d_device, fvf, declaration,
            &d3d8_vertexdeclaration_wined3d_parent_ops, &declaration->wined3d_vertex_declaration);
    if (FAILED(hr))
    {
        WARN("Failed to create wined3d vertex declaration, hr %#x.\n", hr);
        return hr;
    }

    return D3D_OK;
}