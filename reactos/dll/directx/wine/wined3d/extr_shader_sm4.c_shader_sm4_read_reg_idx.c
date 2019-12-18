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
struct wined3d_sm4_data {int dummy; } ;
struct wined3d_shader_src_param {int dummy; } ;
struct wined3d_shader_register_index {scalar_t__ offset; struct wined3d_shader_src_param* rel_addr; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINED3D_DATA_INT ; 
 int WINED3D_SM4_ADDRESSING_OFFSET ; 
 int WINED3D_SM4_ADDRESSING_RELATIVE ; 
 struct wined3d_shader_src_param* get_src_param (struct wined3d_sm4_data*) ; 
 int /*<<< orphan*/  shader_sm4_read_src_param (struct wined3d_sm4_data*,int const**,int const*,int /*<<< orphan*/ ,struct wined3d_shader_src_param*) ; 

__attribute__((used)) static BOOL shader_sm4_read_reg_idx(struct wined3d_sm4_data *priv, const DWORD **ptr, const DWORD *end,
        DWORD addressing, struct wined3d_shader_register_index *reg_idx)
{
    if (addressing & WINED3D_SM4_ADDRESSING_RELATIVE)
    {
        struct wined3d_shader_src_param *rel_addr = get_src_param(priv);

        if (!(reg_idx->rel_addr = rel_addr))
        {
            ERR("Failed to get src param for relative addressing.\n");
            return FALSE;
        }

        if (addressing & WINED3D_SM4_ADDRESSING_OFFSET)
            reg_idx->offset = *(*ptr)++;
        else
            reg_idx->offset = 0;
        shader_sm4_read_src_param(priv, ptr, end, WINED3D_DATA_INT, rel_addr);
    }
    else
    {
        reg_idx->rel_addr = NULL;
        reg_idx->offset = *(*ptr)++;
    }

    return TRUE;
}