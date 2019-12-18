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
struct wined3d_texture {int /*<<< orphan*/ * pow2_matrix; } ;
struct wined3d_state {struct wined3d_texture** textures; } ;
struct wined3d_gl_info {int dummy; } ;
struct TYPE_2__ {int active; unsigned char* idx; size_t num_consts; } ;
struct arb_ps_np2fixup_info {scalar_t__ offset; TYPE_1__ super; } ;
typedef  int WORD ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 int MAX_FRAGMENT_SAMPLERS ; 
 int /*<<< orphan*/  glProgramEnvParameter4fvARB (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shader_arb_load_np2fixup_constants(const struct arb_ps_np2fixup_info *fixup,
        const struct wined3d_gl_info *gl_info, const struct wined3d_state *state)
{
    GLfloat np2fixup_constants[4 * MAX_FRAGMENT_SAMPLERS];
    WORD active = fixup->super.active;
    UINT i;

    if (!active)
        return;

    for (i = 0; active; active >>= 1, ++i)
    {
        const struct wined3d_texture *tex = state->textures[i];
        unsigned char idx = fixup->super.idx[i];
        GLfloat *tex_dim = &np2fixup_constants[(idx >> 1) * 4];

        if (!(active & 1))
            continue;

        if (!tex)
        {
            ERR("Nonexistent texture is flagged for NP2 texcoord fixup.\n");
            continue;
        }

        if (idx % 2)
        {
            tex_dim[2] = tex->pow2_matrix[0];
            tex_dim[3] = tex->pow2_matrix[5];
        }
        else
        {
            tex_dim[0] = tex->pow2_matrix[0];
            tex_dim[1] = tex->pow2_matrix[5];
        }
    }

    for (i = 0; i < fixup->super.num_consts; ++i)
    {
        GL_EXTCALL(glProgramEnvParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB,
                fixup->offset + i, &np2fixup_constants[i * 4]));
    }
}