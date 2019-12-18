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
struct d3dx_sampler {int dummy; } ;
struct d3dx_parameter {char* data; scalar_t__ class; int type; int /*<<< orphan*/  element_count; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ D3DXPC_OBJECT ; 
#define  D3DXPT_PIXELSHADER 140 
#define  D3DXPT_SAMPLER 139 
#define  D3DXPT_SAMPLER1D 138 
#define  D3DXPT_SAMPLER2D 137 
#define  D3DXPT_SAMPLER3D 136 
#define  D3DXPT_SAMPLERCUBE 135 
#define  D3DXPT_STRING 134 
#define  D3DXPT_TEXTURE 133 
#define  D3DXPT_TEXTURE1D 132 
#define  D3DXPT_TEXTURE2D 131 
#define  D3DXPT_TEXTURE3D 130 
#define  D3DXPT_TEXTURECUBE 129 
#define  D3DXPT_VERTEXSHADER 128 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_d3dxparameter_type (int) ; 
 int /*<<< orphan*/  free_sampler (struct d3dx_sampler*) ; 

__attribute__((used)) static void free_parameter_data(struct d3dx_parameter *param, BOOL child)
{
    if (!param->data)
        return;
    if (param->class == D3DXPC_OBJECT && !param->element_count)
    {
        switch (param->type)
        {
            case D3DXPT_STRING:
                HeapFree(GetProcessHeap(), 0, *(char **)param->data);
                break;

            case D3DXPT_TEXTURE:
            case D3DXPT_TEXTURE1D:
            case D3DXPT_TEXTURE2D:
            case D3DXPT_TEXTURE3D:
            case D3DXPT_TEXTURECUBE:
            case D3DXPT_PIXELSHADER:
            case D3DXPT_VERTEXSHADER:
                if (*(IUnknown **)param->data) IUnknown_Release(*(IUnknown **)param->data);
                break;

            case D3DXPT_SAMPLER:
            case D3DXPT_SAMPLER1D:
            case D3DXPT_SAMPLER2D:
            case D3DXPT_SAMPLER3D:
            case D3DXPT_SAMPLERCUBE:
                free_sampler((struct d3dx_sampler *)param->data);
                break;

            default:
                FIXME("Unhandled type %s\n", debug_d3dxparameter_type(param->type));
                break;
        }
    }
    if (!child)
        HeapFree(GetProcessHeap(), 0, param->data);
}