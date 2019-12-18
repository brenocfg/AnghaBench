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
struct d3d9_query {int refcount; int data_size; int /*<<< orphan*/ * parent_device; int /*<<< orphan*/  wined3d_query; TYPE_1__ IDirect3DQuery9_iface; } ;
struct d3d9_device {int /*<<< orphan*/  IDirect3DDevice9Ex_iface; int /*<<< orphan*/  wined3d_device; } ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int D3DQUERYTYPE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int D3DERR_NOTAVAILABLE ; 
 int D3DQUERYTYPE_MEMORYPRESSURE ; 
 int D3DQUERYTYPE_OCCLUSION ; 
 int D3DQUERYTYPE_TIMESTAMPDISJOINT ; 
 int D3D_OK ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9Ex_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  d3d9_null_wined3d_parent_ops ; 
 int /*<<< orphan*/  d3d9_query_vtbl ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 
 int wined3d_query_create (int /*<<< orphan*/ ,int,struct d3d9_query*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wined3d_query_get_data_size (int /*<<< orphan*/ ) ; 

HRESULT query_init(struct d3d9_query *query, struct d3d9_device *device, D3DQUERYTYPE type)
{
    HRESULT hr;

    if (type > D3DQUERYTYPE_MEMORYPRESSURE)
    {
        if (type == 0x16)
            FIXME("Undocumented query %#x created.\n", type);
        else
            WARN("Invalid query type %#x.\n", type);

        return D3DERR_NOTAVAILABLE;
    }

    query->IDirect3DQuery9_iface.lpVtbl = &d3d9_query_vtbl;
    query->refcount = 1;

    wined3d_mutex_lock();
    if (FAILED(hr = wined3d_query_create(device->wined3d_device, type,
            query, &d3d9_null_wined3d_parent_ops, &query->wined3d_query)))
    {
        wined3d_mutex_unlock();
        WARN("Failed to create wined3d query, hr %#x.\n", hr);
        return hr;
    }

    if (type == D3DQUERYTYPE_OCCLUSION)
        query->data_size = sizeof(DWORD);
    else if (type == D3DQUERYTYPE_TIMESTAMPDISJOINT)
        query->data_size = sizeof(BOOL);
    else
        query->data_size = wined3d_query_get_data_size(query->wined3d_query);
    wined3d_mutex_unlock();

    query->parent_device = &device->IDirect3DDevice9Ex_iface;
    IDirect3DDevice9Ex_AddRef(query->parent_device);

    return D3D_OK;
}