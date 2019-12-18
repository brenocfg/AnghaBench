#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ element_count; } ;
struct TYPE_5__ {scalar_t__ element_count; } ;
struct TYPE_4__ {scalar_t__ element_count; } ;
struct wined3d_shader_desc {scalar_t__ const* byte_code; size_t byte_code_size; int max_version; TYPE_3__ patch_constant_signature; TYPE_2__ output_signature; TYPE_1__ input_signature; int /*<<< orphan*/  format; } ;
struct d3d8_vertex_shader {int /*<<< orphan*/  wined3d_shader; int /*<<< orphan*/  vertex_declaration; } ;
struct d3d8_device {int /*<<< orphan*/  wined3d_device; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int D3DVSD_TOKENTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 scalar_t__ D3DVSDE_NORMAL ; 
 scalar_t__ D3DVSDT_FLOAT3 ; 
 scalar_t__ const D3DVSD_DATATYPEMASK ; 
 scalar_t__ const D3DVSD_DATATYPESHIFT ; 
 scalar_t__ const D3DVSD_END () ; 
 scalar_t__ const D3DVSD_TOKENTYPEMASK ; 
 scalar_t__ const D3DVSD_TOKENTYPESHIFT ; 
 int D3DVSD_TOKEN_STREAMDATA ; 
 scalar_t__ const D3DVSD_VERTEXREGMASK ; 
 scalar_t__ const D3DVSD_VERTEXREGSHIFT ; 
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  WINED3D_SHADER_BYTE_CODE_FORMAT_SM1 ; 
 int /*<<< orphan*/  d3d8_vertex_declaration_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_vertexshader_create_vertexdeclaration (struct d3d8_device*,scalar_t__ const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d8_vertexshader_wined3d_parent_ops ; 
 int /*<<< orphan*/  load_local_constants (scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_token (scalar_t__ const*) ; 
 int /*<<< orphan*/  wined3d_mutex_lock () ; 
 int /*<<< orphan*/  wined3d_mutex_unlock () ; 
 int /*<<< orphan*/  wined3d_shader_create_vs (int /*<<< orphan*/ ,struct wined3d_shader_desc*,struct d3d8_vertex_shader*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT d3d8_vertex_shader_init(struct d3d8_vertex_shader *shader, struct d3d8_device *device,
        const DWORD *declaration, const DWORD *byte_code, DWORD shader_handle, DWORD usage)
{
    const DWORD *token = declaration;
    HRESULT hr;

    /* Test if the vertex declaration is valid. */
    while (D3DVSD_END() != *token)
    {
        D3DVSD_TOKENTYPE token_type = ((*token & D3DVSD_TOKENTYPEMASK) >> D3DVSD_TOKENTYPESHIFT);

        if (token_type == D3DVSD_TOKEN_STREAMDATA && !(token_type & 0x10000000))
        {
            DWORD type = ((*token & D3DVSD_DATATYPEMASK) >> D3DVSD_DATATYPESHIFT);
            DWORD reg  = ((*token & D3DVSD_VERTEXREGMASK) >> D3DVSD_VERTEXREGSHIFT);

            if (reg == D3DVSDE_NORMAL && type != D3DVSDT_FLOAT3 && !byte_code)
            {
                WARN("Attempt to use a non-FLOAT3 normal with the fixed-function function\n");
                return D3DERR_INVALIDCALL;
            }
        }
        token += parse_token(token);
    }

    hr = d3d8_vertexshader_create_vertexdeclaration(device, declaration, shader_handle, &shader->vertex_declaration);
    if (FAILED(hr))
    {
        WARN("Failed to create vertex declaration, hr %#x.\n", hr);
        return hr;
    }

    if (byte_code)
    {
        struct wined3d_shader_desc desc;

        if (usage)
            FIXME("Usage %#x not implemented.\n", usage);

        desc.byte_code = byte_code;
        desc.byte_code_size = ~(size_t)0;
        desc.format = WINED3D_SHADER_BYTE_CODE_FORMAT_SM1;
        desc.input_signature.element_count = 0;
        desc.output_signature.element_count = 0;
        desc.patch_constant_signature.element_count = 0;
        desc.max_version = 1;

        wined3d_mutex_lock();
        hr = wined3d_shader_create_vs(device->wined3d_device, &desc, shader,
                &d3d8_vertexshader_wined3d_parent_ops, &shader->wined3d_shader);
        wined3d_mutex_unlock();
        if (FAILED(hr))
        {
            WARN("Failed to create wined3d vertex shader, hr %#x.\n", hr);
            d3d8_vertex_declaration_destroy(shader->vertex_declaration);
            return hr;
        }

        load_local_constants(declaration, shader->wined3d_shader);
    }

    return D3D_OK;
}