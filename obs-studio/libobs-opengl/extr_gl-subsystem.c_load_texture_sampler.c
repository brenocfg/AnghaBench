#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  gl_target; TYPE_2__* cur_sampler; } ;
typedef  TYPE_1__ gs_texture_t ;
struct TYPE_10__ {int /*<<< orphan*/  max_anisotropy; int /*<<< orphan*/  address_w; int /*<<< orphan*/  address_v; int /*<<< orphan*/  address_u; int /*<<< orphan*/  mag_filter; int /*<<< orphan*/  min_filter; } ;
typedef  TYPE_2__ gs_samplerstate_t ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 scalar_t__ GLAD_GL_EXT_texture_filter_anisotropic ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MAX_ANISOTROPY_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_R ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  apply_swizzle (TYPE_1__*) ; 
 int /*<<< orphan*/  gl_tex_param_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gs_texture_is_rect (TYPE_1__*) ; 
 int /*<<< orphan*/  samplerstate_addref (TYPE_2__*) ; 
 int /*<<< orphan*/  samplerstate_release (TYPE_2__*) ; 
 int /*<<< orphan*/  strip_mipmap_filter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool load_texture_sampler(gs_texture_t *tex, gs_samplerstate_t *ss)
{
	bool success = true;
	GLint min_filter;

	if (tex->cur_sampler == ss)
		return true;

	if (tex->cur_sampler)
		samplerstate_release(tex->cur_sampler);
	tex->cur_sampler = ss;
	if (!ss)
		return true;

	samplerstate_addref(ss);

	min_filter = ss->min_filter;
	if (gs_texture_is_rect(tex))
		strip_mipmap_filter(&min_filter);

	if (!gl_tex_param_i(tex->gl_target, GL_TEXTURE_MIN_FILTER, min_filter))
		success = false;
	if (!gl_tex_param_i(tex->gl_target, GL_TEXTURE_MAG_FILTER,
			    ss->mag_filter))
		success = false;
	if (!gl_tex_param_i(tex->gl_target, GL_TEXTURE_WRAP_S, ss->address_u))
		success = false;
	if (!gl_tex_param_i(tex->gl_target, GL_TEXTURE_WRAP_T, ss->address_v))
		success = false;
	if (!gl_tex_param_i(tex->gl_target, GL_TEXTURE_WRAP_R, ss->address_w))
		success = false;
	if (GLAD_GL_EXT_texture_filter_anisotropic) {
		if (!gl_tex_param_i(tex->gl_target,
				    GL_TEXTURE_MAX_ANISOTROPY_EXT,
				    ss->max_anisotropy))
			success = false;
	}

	apply_swizzle(tex);

	return success;
}