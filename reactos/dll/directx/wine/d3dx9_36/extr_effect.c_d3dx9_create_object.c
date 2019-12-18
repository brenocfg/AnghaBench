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
struct d3dx_parameter {int type; scalar_t__ data; } ;
struct d3dx_object {void* creation_failed; int /*<<< orphan*/  data; int /*<<< orphan*/  size; struct d3dx_parameter* param; } ;
struct d3dx9_base_effect {TYPE_1__* effect; } ;
struct IDirect3DDevice9 {int dummy; } ;
struct TYPE_2__ {struct IDirect3DDevice9* device; } ;
typedef  int /*<<< orphan*/  IDirect3DVertexShader9 ;
typedef  int /*<<< orphan*/  IDirect3DPixelShader9 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
#define  D3DXPT_PIXELSHADER 130 
#define  D3DXPT_STRING 129 
#define  D3DXPT_VERTEXSHADER 128 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_CreatePixelShader (struct IDirect3DDevice9*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DDevice9_CreateVertexShader (struct IDirect3DDevice9*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT d3dx9_create_object(struct d3dx9_base_effect *base, struct d3dx_object *object)
{
    struct d3dx_parameter *param = object->param;
    struct IDirect3DDevice9 *device = base->effect->device;
    HRESULT hr;

    if (*(char **)param->data)
        ERR("Parameter data already allocated.\n");

    switch (param->type)
    {
        case D3DXPT_STRING:
            *(char **)param->data = HeapAlloc(GetProcessHeap(), 0, object->size);
            if (!*(char **)param->data)
            {
                ERR("Out of memory.\n");
                return E_OUTOFMEMORY;
            }
            memcpy(*(char **)param->data, object->data, object->size);
            break;
        case D3DXPT_VERTEXSHADER:
            if (FAILED(hr = IDirect3DDevice9_CreateVertexShader(device, object->data,
                    (IDirect3DVertexShader9 **)param->data)))
            {
                WARN("Failed to create vertex shader.\n");
                object->creation_failed = TRUE;
            }
            break;
        case D3DXPT_PIXELSHADER:
            if (FAILED(hr = IDirect3DDevice9_CreatePixelShader(device, object->data,
                    (IDirect3DPixelShader9 **)param->data)))
            {
                WARN("Failed to create pixel shader.\n");
                object->creation_failed = TRUE;
            }
            break;
        default:
            break;
    }
    return D3D_OK;
}