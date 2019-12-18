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
struct wined3d_sm4_data {TYPE_3__* src_param; } ;
struct wined3d_shader_instruction {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fp_body_idx; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
struct TYPE_6__ {TYPE_2__ reg; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_DATA_OPAQUE ; 
 int /*<<< orphan*/  shader_sm4_read_src_param (struct wined3d_sm4_data*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void shader_sm5_read_fcall(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    priv->src_param[0].reg.u.fp_body_idx = *tokens++;
    shader_sm4_read_src_param(priv, &tokens, &tokens[token_count], WINED3D_DATA_OPAQUE, &priv->src_param[0]);
}