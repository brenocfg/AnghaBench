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
struct wined3d_texture {int flags; } ;
struct wined3d_state {struct wined3d_texture** textures; } ;
struct wined3d_context {unsigned int lastWasPow2Texture; int /*<<< orphan*/  constant_update_mask; } ;
typedef  size_t DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 size_t MAX_TEXTURES ; 
 size_t STATE_SAMPLER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_FFP_TEXMATRIX ; 
 int WINED3D_TEXTURE_POW2_MAT_IDENT ; 

__attribute__((used)) static void glsl_vertex_pipe_texmatrix_np2(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    DWORD sampler = state_id - STATE_SAMPLER(0);
    const struct wined3d_texture *texture = state->textures[sampler];
    BOOL np2;

    if (!texture)
        return;

    if (sampler >= MAX_TEXTURES)
        return;

    if ((np2 = !(texture->flags & WINED3D_TEXTURE_POW2_MAT_IDENT))
            || context->lastWasPow2Texture & (1u << sampler))
    {
        if (np2)
            context->lastWasPow2Texture |= 1u << sampler;
        else
            context->lastWasPow2Texture &= ~(1u << sampler);

        context->constant_update_mask |= WINED3D_SHADER_CONST_FFP_TEXMATRIX;
    }
}