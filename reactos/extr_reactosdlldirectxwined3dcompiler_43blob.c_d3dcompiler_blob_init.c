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
struct d3dcompiler_blob {int refcount; int /*<<< orphan*/  data; int /*<<< orphan*/  size; TYPE_1__ ID3DBlob_iface; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  d3dcompiler_blob_vtbl ; 

__attribute__((used)) static HRESULT d3dcompiler_blob_init(struct d3dcompiler_blob *blob, SIZE_T data_size)
{
    blob->ID3DBlob_iface.lpVtbl = &d3dcompiler_blob_vtbl;
    blob->refcount = 1;
    blob->size = data_size;

    blob->data = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, data_size);
    if (!blob->data)
    {
        ERR("Failed to allocate D3D blob data memory\n");
        return E_OUTOFMEMORY;
    }

    return S_OK;
}