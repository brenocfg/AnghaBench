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
struct d3d9_vertex_declaration {int dummy; } ;
struct d3d9_device {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3DVERTEXELEMENT9 ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3d9_vertex_declaration*) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 struct d3d9_vertex_declaration* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (struct d3d9_vertex_declaration*) ; 
 int /*<<< orphan*/  vertexdeclaration_init (struct d3d9_vertex_declaration*,struct d3d9_device*,int /*<<< orphan*/  const*) ; 

HRESULT d3d9_vertex_declaration_create(struct d3d9_device *device,
        const D3DVERTEXELEMENT9 *elements, struct d3d9_vertex_declaration **declaration)
{
    struct d3d9_vertex_declaration *object;
    HRESULT hr;

    if (!(object = heap_alloc_zero(sizeof(*object))))
        return E_OUTOFMEMORY;

    hr = vertexdeclaration_init(object, device, elements);
    if (FAILED(hr))
    {
        WARN("Failed to initialize vertex declaration, hr %#x.\n", hr);
        heap_free(object);
        return hr;
    }

    TRACE("Created vertex declaration %p.\n", object);
    *declaration = object;

    return D3D_OK;
}