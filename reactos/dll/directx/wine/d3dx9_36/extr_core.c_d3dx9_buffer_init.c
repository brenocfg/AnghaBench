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
struct ID3DXBufferImpl {int ref; int /*<<< orphan*/  buffer; int /*<<< orphan*/  size; TYPE_1__ ID3DXBuffer_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3DXBufferImpl_Vtbl ; 

__attribute__((used)) static HRESULT d3dx9_buffer_init(struct ID3DXBufferImpl *buffer, DWORD size)
{
    buffer->ID3DXBuffer_iface.lpVtbl = &ID3DXBufferImpl_Vtbl;
    buffer->ref = 1;
    buffer->size = size;

    buffer->buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    if (!buffer->buffer)
    {
        ERR("Failed to allocate buffer memory\n");
        return E_OUTOFMEMORY;
    }

    return D3D_OK;
}