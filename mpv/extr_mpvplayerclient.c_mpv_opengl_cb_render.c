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
typedef  int /*<<< orphan*/  mpv_opengl_cb_context ;

/* Variables and functions */
 int mpv_opengl_cb_draw (int /*<<< orphan*/ *,int,int,int) ; 

int mpv_opengl_cb_render(mpv_opengl_cb_context *ctx, int fbo, int vp[4])
{
    return mpv_opengl_cb_draw(ctx, fbo, vp[2], vp[3]);
}