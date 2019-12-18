#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* p_glDeleteTextures ) (int,scalar_t__*) ;} ;
struct TYPE_4__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; } ;
struct wined3d_device {int dummy; } ;
struct gl_texture {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  context_gl_resource_released (struct wined3d_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__*) ; 

__attribute__((used)) static void gltexture_delete(struct wined3d_device *device, const struct wined3d_gl_info *gl_info,
        struct gl_texture *tex)
{
    context_gl_resource_released(device, tex->name, FALSE);
    gl_info->gl_ops.gl.p_glDeleteTextures(1, &tex->name);
    tex->name = 0;
}