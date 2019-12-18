#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct fbo_info {scalar_t__ width; scalar_t__ height; scalar_t__ format; int /*<<< orphan*/ * cur_zstencil_buffer; scalar_t__ cur_render_side; int /*<<< orphan*/ * cur_render_target; int /*<<< orphan*/  fbo; } ;
struct TYPE_3__ {scalar_t__ format; struct fbo_info* fbo; } ;
typedef  TYPE_1__ gs_texture_t ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 struct fbo_info* bmalloc (int) ; 
 int /*<<< orphan*/  glGenFramebuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

struct fbo_info *get_fbo(gs_texture_t *tex, uint32_t width, uint32_t height)
{
	if (tex->fbo && tex->fbo->width == width &&
	    tex->fbo->height == height && tex->fbo->format == tex->format)
		return tex->fbo;

	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	if (!gl_success("glGenFramebuffers"))
		return NULL;

	tex->fbo = bmalloc(sizeof(struct fbo_info));
	tex->fbo->fbo = fbo;
	tex->fbo->width = width;
	tex->fbo->height = height;
	tex->fbo->format = tex->format;
	tex->fbo->cur_render_target = NULL;
	tex->fbo->cur_render_side = 0;
	tex->fbo->cur_zstencil_buffer = NULL;

	return tex->fbo;
}