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
struct wined3d_sm4_data {int /*<<< orphan*/ * src_param; } ;
struct wined3d_shader_instruction {int /*<<< orphan*/  flags; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_DATA_UINT ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONDITIONAL_OP_NZ ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONDITIONAL_OP_Z ; 
 int WINED3D_SM4_CONDITIONAL_NZ ; 
 int /*<<< orphan*/  shader_sm4_read_src_param (struct wined3d_sm4_data*,int const**,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shader_sm4_read_conditional_op(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    shader_sm4_read_src_param(priv, &tokens, &tokens[token_count], WINED3D_DATA_UINT, &priv->src_param[0]);
    ins->flags = (opcode_token & WINED3D_SM4_CONDITIONAL_NZ) ?
            WINED3D_SHADER_CONDITIONAL_OP_NZ : WINED3D_SHADER_CONDITIONAL_OP_Z;
}