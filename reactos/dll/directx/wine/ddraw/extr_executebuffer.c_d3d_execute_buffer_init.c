#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dwFlags; scalar_t__ dwBufferSize; int /*<<< orphan*/ * lpData; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3d_execute_buffer {int ref; TYPE_3__ desc; int /*<<< orphan*/  need_free; struct d3d_device* d3ddev; TYPE_1__ IDirect3DExecuteBuffer_iface; } ;
struct d3d_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dwSize; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ D3DEXECUTEBUFFERDESC ;

/* Variables and functions */
 int D3DDEB_BUFSIZE ; 
 int D3DDEB_LPDATA ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  DDERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  d3d_execute_buffer_vtbl ; 
 int /*<<< orphan*/ * heap_alloc_zero (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

HRESULT d3d_execute_buffer_init(struct d3d_execute_buffer *execute_buffer,
        struct d3d_device *device, D3DEXECUTEBUFFERDESC *desc)
{
    execute_buffer->IDirect3DExecuteBuffer_iface.lpVtbl = &d3d_execute_buffer_vtbl;
    execute_buffer->ref = 1;
    execute_buffer->d3ddev = device;

    /* Initializes memory */
    memcpy(&execute_buffer->desc, desc, desc->dwSize);

    /* No buffer given */
    if (!(execute_buffer->desc.dwFlags & D3DDEB_LPDATA))
        execute_buffer->desc.lpData = NULL;

    /* No buffer size given */
    if (!(execute_buffer->desc.dwFlags & D3DDEB_BUFSIZE))
        execute_buffer->desc.dwBufferSize = 0;

    /* Create buffer if asked */
    if (!execute_buffer->desc.lpData && execute_buffer->desc.dwBufferSize)
    {
        execute_buffer->need_free = TRUE;
        if (!(execute_buffer->desc.lpData = heap_alloc_zero(execute_buffer->desc.dwBufferSize)))
        {
            ERR("Failed to allocate execute buffer data.\n");
            return DDERR_OUTOFMEMORY;
        }
    }

    execute_buffer->desc.dwFlags |= D3DDEB_LPDATA;

    return D3D_OK;
}