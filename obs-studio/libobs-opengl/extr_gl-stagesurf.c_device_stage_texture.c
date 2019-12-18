#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  texture; } ;
struct gs_texture_2d {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_6__ {int /*<<< orphan*/  gl_type; int /*<<< orphan*/  gl_format; int /*<<< orphan*/  pack_buffer; } ;
typedef  TYPE_2__ gs_stagesurf_t ;
typedef  int /*<<< orphan*/  gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PIXEL_PACK_BUFFER ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  can_stage (TYPE_2__*,struct gs_texture_2d*) ; 
 int /*<<< orphan*/  glGetTexImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_bind_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_bind_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void device_stage_texture(gs_device_t *device, gs_stagesurf_t *dst,
			  gs_texture_t *src)
{
	struct gs_texture_2d *tex2d = (struct gs_texture_2d *)src;
	if (!can_stage(dst, tex2d))
		goto failed;

	if (!gl_bind_buffer(GL_PIXEL_PACK_BUFFER, dst->pack_buffer))
		goto failed;
	if (!gl_bind_texture(GL_TEXTURE_2D, tex2d->base.texture))
		goto failed;

	glGetTexImage(GL_TEXTURE_2D, 0, dst->gl_format, dst->gl_type, 0);
	if (!gl_success("glGetTexImage"))
		goto failed;

	gl_bind_texture(GL_TEXTURE_2D, 0);
	gl_bind_buffer(GL_PIXEL_PACK_BUFFER, 0);
	return;

failed:
	gl_bind_buffer(GL_PIXEL_PACK_BUFFER, 0);
	gl_bind_texture(GL_TEXTURE_2D, 0);
	blog(LOG_ERROR, "device_stage_texture (GL) failed");

	UNUSED_PARAMETER(device);
}