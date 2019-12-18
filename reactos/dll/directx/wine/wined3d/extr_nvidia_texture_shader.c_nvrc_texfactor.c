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
struct wined3d_state {int /*<<< orphan*/ * render_states; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct wined3d_color {int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CONSTANT_COLOR0_NV ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 size_t WINED3D_RS_TEXTUREFACTOR ; 
 int /*<<< orphan*/  glCombinerParameterfvNV (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_color_from_d3dcolor (struct wined3d_color*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvrc_texfactor(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_color color;

    wined3d_color_from_d3dcolor(&color, state->render_states[WINED3D_RS_TEXTUREFACTOR]);
    GL_EXTCALL(glCombinerParameterfvNV(GL_CONSTANT_COLOR0_NV, &color.r));
}