#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3dcompiler_shader_reflection_variable {int start_offset; int size; int flags; int /*<<< orphan*/  default_value; int /*<<< orphan*/  type; int /*<<< orphan*/  name; struct d3dcompiler_shader_reflection_constant_buffer* constant_buffer; TYPE_1__ ID3D11ShaderReflectionVariable_iface; } ;
struct d3dcompiler_shader_reflection_constant_buffer {int variable_count; struct d3dcompiler_shader_reflection_variable* variables; TYPE_2__* reflection; } ;
struct TYPE_4__ {int target; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int D3DCOMPILER_SHADER_TARGET_VERSION_MASK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct d3dcompiler_shader_reflection_variable* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct d3dcompiler_shader_reflection_variable*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  copy_name (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_value (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  d3dcompiler_shader_reflection_variable_vtbl ; 
 int debugstr_a (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_variable (struct d3dcompiler_shader_reflection_variable*) ; 
 int /*<<< orphan*/  get_reflection_type (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  read_dword (char const**,int*) ; 
 int /*<<< orphan*/  skip_dword_unknown (char const**,int) ; 

__attribute__((used)) static HRESULT d3dcompiler_parse_variables(struct d3dcompiler_shader_reflection_constant_buffer *cb,
        const char *data, DWORD data_size, const char *ptr)
{
    struct d3dcompiler_shader_reflection_variable *variables;
    unsigned int i;
    HRESULT hr;

    variables = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cb->variable_count * sizeof(*variables));
    if (!variables)
    {
        ERR("Failed to allocate variables memory.\n");
        return E_OUTOFMEMORY;
    }

    for (i = 0; i < cb->variable_count; i++)
    {
        struct d3dcompiler_shader_reflection_variable *v = &variables[i];
        DWORD offset;

        v->ID3D11ShaderReflectionVariable_iface.lpVtbl = &d3dcompiler_shader_reflection_variable_vtbl;
        v->constant_buffer = cb;

        read_dword(&ptr, &offset);
        if (!copy_name(data + offset, &v->name))
        {
            ERR("Failed to copy name.\n");
            hr = E_OUTOFMEMORY;
            goto err_out;
        }
        TRACE("Variable name: %s.\n", debugstr_a(v->name));

        read_dword(&ptr, &v->start_offset);
        TRACE("Variable offset: %u\n", v->start_offset);

        read_dword(&ptr, &v->size);
        TRACE("Variable size: %u\n", v->size);

        read_dword(&ptr, &v->flags);
        TRACE("Variable flags: %u\n", v->flags);

        read_dword(&ptr, &offset);
        TRACE("Variable type offset: %x\n", offset);
        v->type = get_reflection_type(cb->reflection, data, offset);
        if (!v->type)
        {
            ERR("Failed to get type.\n");
            hr = E_FAIL;
            goto err_out;
        }

        read_dword(&ptr, &offset);
        TRACE("Variable default value offset: %x\n", offset);
        if (!copy_value(data + offset, &v->default_value, offset ? v->size : 0))
        {
            ERR("Failed to copy name.\n");
            hr = E_OUTOFMEMORY;
            goto err_out;
        }

        if ((cb->reflection->target & D3DCOMPILER_SHADER_TARGET_VERSION_MASK) >= 0x500)
            skip_dword_unknown(&ptr, 4);
    }

    cb->variables = variables;

    return S_OK;

err_out:
    for (i = 0; i < cb->variable_count; i++)
    {
        free_variable(&variables[i]);
    }
    HeapFree(GetProcessHeap(), 0, variables);
    return hr;
}