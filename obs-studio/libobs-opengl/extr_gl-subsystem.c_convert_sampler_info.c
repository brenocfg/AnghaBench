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
struct gs_sampler_state {int max_anisotropy; void* address_w; void* address_v; void* address_u; int /*<<< orphan*/  mag_filter; int /*<<< orphan*/  min_filter; } ;
struct gs_sampler_info {int max_anisotropy; int /*<<< orphan*/  address_w; int /*<<< orphan*/  address_v; int /*<<< orphan*/  address_u; int /*<<< orphan*/  filter; } ;
typedef  int GLint ;

/* Variables and functions */
 scalar_t__ GLAD_GL_EXT_texture_filter_anisotropic ; 
 int /*<<< orphan*/  GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int,int,int) ; 
 void* convert_address_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void convert_sampler_info(struct gs_sampler_state *sampler,
			  const struct gs_sampler_info *info)
{
	GLint max_anisotropy_max;
	convert_filter(info->filter, &sampler->min_filter,
		       &sampler->mag_filter);
	sampler->address_u = convert_address_mode(info->address_u);
	sampler->address_v = convert_address_mode(info->address_v);
	sampler->address_w = convert_address_mode(info->address_w);
	sampler->max_anisotropy = info->max_anisotropy;

	max_anisotropy_max = 1;
	if (GLAD_GL_EXT_texture_filter_anisotropic) {
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,
			      &max_anisotropy_max);
		gl_success("glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT)");
	}

	if (1 <= sampler->max_anisotropy &&
	    sampler->max_anisotropy <= max_anisotropy_max)
		return;

	if (sampler->max_anisotropy < 1)
		sampler->max_anisotropy = 1;
	else if (sampler->max_anisotropy > max_anisotropy_max)
		sampler->max_anisotropy = max_anisotropy_max;

	blog(LOG_DEBUG,
	     "convert_sampler_info: 1 <= max_anisotropy <= "
	     "%d violated, selected: %d, set: %d",
	     max_anisotropy_max, info->max_anisotropy, sampler->max_anisotropy);
}