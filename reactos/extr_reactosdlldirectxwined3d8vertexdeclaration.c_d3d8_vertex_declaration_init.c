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
struct wined3d_vertex_element {int dummy; } ;
struct d3d8_vertex_declaration {struct wined3d_vertex_element* elements; int /*<<< orphan*/  wined3d_vertex_declaration; int /*<<< orphan*/  elements_size; int /*<<< orphan*/  shader_handle; } ;
struct d3d8_device {int /*<<< orphan*/  wined3d_device; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_wined3d_declaration (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,struct wined3d_vertex_element**) ; 
 int /*<<< orphan*/  d3d8_vertexdeclaration_wined3d_parent_ops ; 
 struct wined3d_vertex_element* heap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (struct wined3d_vertex_element*) ; 
 int /*<<< orphan*/  memcpy (struct wined3d_vertex_element*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 
 int /*<<< orphan*/  wined3d_vertex_declaration_create (int /*<<< orphan*/ ,struct wined3d_vertex_element*,int /*<<< orphan*/ ,struct d3d8_vertex_declaration*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT d3d8_vertex_declaration_init(struct d3d8_vertex_declaration *declaration,
        struct d3d8_device *device, const DWORD *elements, DWORD shader_handle)
{
    struct wined3d_vertex_element *wined3d_elements;
    UINT wined3d_element_count;
    HRESULT hr;

    declaration->shader_handle = shader_handle;

    wined3d_element_count = convert_to_wined3d_declaration(elements, &declaration->elements_size, &wined3d_elements);
    if (!(declaration->elements = heap_alloc(declaration->elements_size)))
    {
        ERR("Failed to allocate vertex declaration elements memory.\n");
        heap_free(wined3d_elements);
        return E_OUTOFMEMORY;
    }

    memcpy(declaration->elements, elements, declaration->elements_size);

    wined3d_mutex_lock();
    hr = wined3d_vertex_declaration_create(device->wined3d_device, wined3d_elements, wined3d_element_count,
            declaration, &d3d8_vertexdeclaration_wined3d_parent_ops, &declaration->wined3d_vertex_declaration);
    wined3d_mutex_unlock();
    heap_free(wined3d_elements);
    if (FAILED(hr))
    {
        WARN("Failed to create wined3d vertex declaration, hr %#x.\n", hr);
        heap_free(declaration->elements);
        return hr;
    }

    return D3D_OK;
}