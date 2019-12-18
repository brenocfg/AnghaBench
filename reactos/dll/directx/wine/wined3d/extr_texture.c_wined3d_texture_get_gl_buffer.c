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
struct wined3d_texture {struct wined3d_swapchain* swapchain; } ;
struct wined3d_swapchain {struct wined3d_texture const** back_buffers; struct wined3d_texture const* front_buffer; } ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,struct wined3d_texture const*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_NONE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

GLenum wined3d_texture_get_gl_buffer(const struct wined3d_texture *texture)
{
    const struct wined3d_swapchain *swapchain = texture->swapchain;

    TRACE("texture %p.\n", texture);

    if (!swapchain)
    {
        ERR("Texture %p is not part of a swapchain.\n", texture);
        return GL_NONE;
    }

    if (texture == swapchain->front_buffer)
    {
        TRACE("Returning GL_FRONT.\n");
        return GL_FRONT;
    }

    if (texture == swapchain->back_buffers[0])
    {
        TRACE("Returning GL_BACK.\n");
        return GL_BACK;
    }

    FIXME("Higher back buffer, returning GL_BACK.\n");
    return GL_BACK;
}