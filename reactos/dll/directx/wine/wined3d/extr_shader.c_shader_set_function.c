#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; unsigned int major; int /*<<< orphan*/  minor; } ;
struct wined3d_shader_reg_maps {TYPE_4__ shader_version; } ;
struct wined3d_shader_frontend {int /*<<< orphan*/  (* shader_init ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct wined3d_shader {int /*<<< orphan*/  output_signature; int /*<<< orphan*/  input_signature; int /*<<< orphan*/  frontend_data; int /*<<< orphan*/  functionLength; int /*<<< orphan*/  function; struct wined3d_shader_frontend* frontend; TYPE_2__* device; struct wined3d_shader_reg_maps reg_maps; } ;
struct TYPE_7__ {unsigned int vs_version; unsigned int hs_version; unsigned int ds_version; unsigned int gs_version; unsigned int ps_version; unsigned int cs_version; } ;
struct wined3d_d3d_info {TYPE_3__ limits; } ;
typedef  enum wined3d_shader_type { ____Placeholder_wined3d_shader_type } wined3d_shader_type ;
struct TYPE_6__ {TYPE_1__* adapter; } ;
struct TYPE_5__ {struct wined3d_d3d_info d3d_info; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_shader*,int /*<<< orphan*/ ,int,unsigned int) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,unsigned int,...) ; 
 int /*<<< orphan*/  WINED3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  WINED3D_OK ; 
#define  WINED3D_SHADER_TYPE_COMPUTE 133 
#define  WINED3D_SHADER_TYPE_DOMAIN 132 
#define  WINED3D_SHADER_TYPE_GEOMETRY 131 
#define  WINED3D_SHADER_TYPE_HULL 130 
#define  WINED3D_SHADER_TYPE_PIXEL 129 
#define  WINED3D_SHADER_TYPE_VERTEX 128 
 int /*<<< orphan*/  d3d_shader ; 
 int /*<<< orphan*/  shader_get_registers_used (struct wined3d_shader*,struct wined3d_shader_frontend const*,struct wined3d_shader_reg_maps*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_trace_init (struct wined3d_shader_frontend const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT shader_set_function(struct wined3d_shader *shader, DWORD float_const_count,
        enum wined3d_shader_type type, unsigned int max_version)
{
    struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    const struct wined3d_shader_frontend *fe;
    HRESULT hr;
    unsigned int backend_version;
    const struct wined3d_d3d_info *d3d_info = &shader->device->adapter->d3d_info;

    TRACE("shader %p, float_const_count %u, type %#x, max_version %u.\n",
            shader, float_const_count, type, max_version);

    fe = shader->frontend;
    if (!(shader->frontend_data = fe->shader_init(shader->function,
            shader->functionLength, &shader->output_signature)))
    {
        FIXME("Failed to initialize frontend.\n");
        return WINED3DERR_INVALIDCALL;
    }

    /* First pass: trace shader. */
    if (TRACE_ON(d3d_shader))
        shader_trace_init(fe, shader->frontend_data);

    /* Second pass: figure out which registers are used, what the semantics are, etc. */
    if (FAILED(hr = shader_get_registers_used(shader, fe, reg_maps, &shader->input_signature,
            &shader->output_signature, float_const_count)))
        return hr;

    if (reg_maps->shader_version.type != type)
    {
        WARN("Wrong shader type %d.\n", reg_maps->shader_version.type);
        return WINED3DERR_INVALIDCALL;
    }
    if (reg_maps->shader_version.major > max_version)
    {
        WARN("Shader version %d not supported by this D3D API version.\n", reg_maps->shader_version.major);
        return WINED3DERR_INVALIDCALL;
    }
    switch (type)
    {
        case WINED3D_SHADER_TYPE_VERTEX:
            backend_version = d3d_info->limits.vs_version;
            break;
        case WINED3D_SHADER_TYPE_HULL:
            backend_version = d3d_info->limits.hs_version;
            break;
        case WINED3D_SHADER_TYPE_DOMAIN:
            backend_version = d3d_info->limits.ds_version;
            break;
        case WINED3D_SHADER_TYPE_GEOMETRY:
            backend_version = d3d_info->limits.gs_version;
            break;
        case WINED3D_SHADER_TYPE_PIXEL:
            backend_version = d3d_info->limits.ps_version;
            break;
        case WINED3D_SHADER_TYPE_COMPUTE:
            backend_version = d3d_info->limits.cs_version;
            break;
        default:
            FIXME("No backend version-checking for this shader type.\n");
            backend_version = 0;
    }
    if (reg_maps->shader_version.major > backend_version)
    {
        WARN("Shader version %d.%d not supported by your GPU with the current shader backend.\n",
                reg_maps->shader_version.major, reg_maps->shader_version.minor);
        return WINED3DERR_INVALIDCALL;
    }

    return WINED3D_OK;
}