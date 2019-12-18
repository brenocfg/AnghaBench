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
struct gs_texture {scalar_t__ format; int /*<<< orphan*/  gl_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ONE ; 
 int /*<<< orphan*/  GL_RED ; 
 int /*<<< orphan*/  GL_TEXTURE_SWIZZLE_A ; 
 int /*<<< orphan*/  GL_TEXTURE_SWIZZLE_B ; 
 int /*<<< orphan*/  GL_TEXTURE_SWIZZLE_G ; 
 int /*<<< orphan*/  GL_TEXTURE_SWIZZLE_R ; 
 scalar_t__ GS_A8 ; 
 int /*<<< orphan*/  gl_tex_param_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void apply_swizzle(struct gs_texture *tex)
{
	if (tex->format == GS_A8) {
		gl_tex_param_i(tex->gl_target, GL_TEXTURE_SWIZZLE_R, GL_ONE);
		gl_tex_param_i(tex->gl_target, GL_TEXTURE_SWIZZLE_G, GL_ONE);
		gl_tex_param_i(tex->gl_target, GL_TEXTURE_SWIZZLE_B, GL_ONE);
		gl_tex_param_i(tex->gl_target, GL_TEXTURE_SWIZZLE_A, GL_RED);
	}
}