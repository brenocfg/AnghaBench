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
struct d3dcompiler_shader_reflection {int instruction_count; int temp_register_count; int dcl_count; int float_instruction_count; int int_instruction_count; int uint_instruction_count; int static_flow_control_count; int dynamic_flow_control_count; int temp_array_count; int array_instruction_count; int cut_instruction_count; int emit_instruction_count; int texture_normal_instructions; int texture_load_instructions; int texture_comp_instructions; int texture_bias_instructions; int texture_gradient_instructions; int mov_instruction_count; int conversion_instruction_count; int input_primitive; int gs_output_topology; int gs_max_output_vertex_count; int c_control_points; int hs_output_primitive; int hs_prtitioning; int tessellator_domain; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  read_dword (char const**,int*) ; 
 int /*<<< orphan*/  skip_dword_unknown (char const**,int) ; 

__attribute__((used)) static HRESULT d3dcompiler_parse_stat(struct d3dcompiler_shader_reflection *r, const char *data, DWORD data_size)
{
    const char *ptr = data;
    DWORD size = data_size >> 2;

    TRACE("Size %u\n", size);

    read_dword(&ptr, &r->instruction_count);
    TRACE("InstructionCount: %u\n", r->instruction_count);

    read_dword(&ptr, &r->temp_register_count);
    TRACE("TempRegisterCount: %u\n", r->temp_register_count);

    skip_dword_unknown(&ptr, 1);

    read_dword(&ptr, &r->dcl_count);
    TRACE("DclCount: %u\n", r->dcl_count);

    read_dword(&ptr, &r->float_instruction_count);
    TRACE("FloatInstructionCount: %u\n", r->float_instruction_count);

    read_dword(&ptr, &r->int_instruction_count);
    TRACE("IntInstructionCount: %u\n", r->int_instruction_count);

    read_dword(&ptr, &r->uint_instruction_count);
    TRACE("UintInstructionCount: %u\n", r->uint_instruction_count);

    read_dword(&ptr, &r->static_flow_control_count);
    TRACE("StaticFlowControlCount: %u\n", r->static_flow_control_count);

    read_dword(&ptr, &r->dynamic_flow_control_count);
    TRACE("DynamicFlowControlCount: %u\n", r->dynamic_flow_control_count);

    skip_dword_unknown(&ptr, 1);

    read_dword(&ptr, &r->temp_array_count);
    TRACE("TempArrayCount: %u\n", r->temp_array_count);

    read_dword(&ptr, &r->array_instruction_count);
    TRACE("ArrayInstructionCount: %u\n", r->array_instruction_count);

    read_dword(&ptr, &r->cut_instruction_count);
    TRACE("CutInstructionCount: %u\n", r->cut_instruction_count);

    read_dword(&ptr, &r->emit_instruction_count);
    TRACE("EmitInstructionCount: %u\n", r->emit_instruction_count);

    read_dword(&ptr, &r->texture_normal_instructions);
    TRACE("TextureNormalInstructions: %u\n", r->texture_normal_instructions);

    read_dword(&ptr, &r->texture_load_instructions);
    TRACE("TextureLoadInstructions: %u\n", r->texture_load_instructions);

    read_dword(&ptr, &r->texture_comp_instructions);
    TRACE("TextureCompInstructions: %u\n", r->texture_comp_instructions);

    read_dword(&ptr, &r->texture_bias_instructions);
    TRACE("TextureBiasInstructions: %u\n", r->texture_bias_instructions);

    read_dword(&ptr, &r->texture_gradient_instructions);
    TRACE("TextureGradientInstructions: %u\n", r->texture_gradient_instructions);

    read_dword(&ptr, &r->mov_instruction_count);
    TRACE("MovInstructionCount: %u\n", r->mov_instruction_count);

    skip_dword_unknown(&ptr, 1);

    read_dword(&ptr, &r->conversion_instruction_count);
    TRACE("ConversionInstructionCount: %u\n", r->conversion_instruction_count);

    skip_dword_unknown(&ptr, 1);

#ifdef __REACTOS__ /* DWORD* cast added */
    read_dword(&ptr, (DWORD*)&r->input_primitive);
#else
    read_dword(&ptr, &r->input_primitive);
#endif
    TRACE("InputPrimitive: %x\n", r->input_primitive);

#ifdef __REACTOS__ /* DWORD* cast added */
    read_dword(&ptr, (DWORD*)&r->gs_output_topology);
#else
    read_dword(&ptr, &r->gs_output_topology);
#endif
    TRACE("GSOutputTopology: %x\n", r->gs_output_topology);

    read_dword(&ptr, &r->gs_max_output_vertex_count);
    TRACE("GSMaxOutputVertexCount: %u\n", r->gs_max_output_vertex_count);

    skip_dword_unknown(&ptr, 2);

    /* old dx10 stat size */
    if (size == 28) return S_OK;

    skip_dword_unknown(&ptr, 1);

    /* dx10 stat size */
    if (size == 29) return S_OK;

    skip_dword_unknown(&ptr, 1);

    read_dword(&ptr, &r->c_control_points);
    TRACE("cControlPoints: %u\n", r->c_control_points);

#ifdef __REACTOS__ /* DWORD* cast added */
    read_dword(&ptr, (DWORD*)&r->hs_output_primitive);
#else
    read_dword(&ptr, &r->hs_output_primitive);
#endif
    TRACE("HSOutputPrimitive: %x\n", r->hs_output_primitive);

#ifdef __REACTOS__ /* DWORD* cast added */
    read_dword(&ptr, (DWORD*)&r->hs_prtitioning);
#else
    read_dword(&ptr, &r->hs_prtitioning);
#endif
    TRACE("HSPartitioning: %x\n", r->hs_prtitioning);

#ifdef __REACTOS__ /* DWORD* cast added */
    read_dword(&ptr, (DWORD*)&r->tessellator_domain);
#else
    read_dword(&ptr, &r->tessellator_domain);
#endif
    TRACE("TessellatorDomain: %x\n", r->tessellator_domain);

    skip_dword_unknown(&ptr, 3);

    /* dx11 stat size */
    if (size == 37) return S_OK;

    FIXME("Unhandled size %u\n", size);

    return E_FAIL;
}