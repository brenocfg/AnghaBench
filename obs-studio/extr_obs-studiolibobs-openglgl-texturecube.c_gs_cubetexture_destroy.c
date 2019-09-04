#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fbo; scalar_t__ texture; } ;
typedef  TYPE_1__ gs_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  fbo_info_destroy (scalar_t__) ; 
 int /*<<< orphan*/  gl_delete_textures (int,scalar_t__*) ; 

void gs_cubetexture_destroy(gs_texture_t *tex)
{
	if (!tex)
		return;

	if (tex->texture)
		gl_delete_textures(1, &tex->texture);

	if (tex->fbo)
		fbo_info_destroy(tex->fbo);

	bfree(tex);
}