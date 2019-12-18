#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wined3d_texture {TYPE_1__* swapchain; } ;
struct wined3d_surface {struct wined3d_texture* container; } ;
typedef  void* UINT ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {void* bottom; void* top; } ;
struct TYPE_8__ {struct wined3d_texture* front_buffer; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,TYPE_3__*) ; 

void surface_translate_drawable_coords(const struct wined3d_surface *surface, HWND window, RECT *rect)
{
    struct wined3d_texture *texture = surface->container;
    POINT offset = {0, 0};
    UINT drawable_height;
    RECT windowsize;

    if (!texture->swapchain)
        return;

    if (texture == texture->swapchain->front_buffer)
    {
        ScreenToClient(window, &offset);
        OffsetRect(rect, offset.x, offset.y);
    }

    GetClientRect(window, &windowsize);
    drawable_height = windowsize.bottom - windowsize.top;

    rect->top = drawable_height - rect->top;
    rect->bottom = drawable_height - rect->bottom;
}