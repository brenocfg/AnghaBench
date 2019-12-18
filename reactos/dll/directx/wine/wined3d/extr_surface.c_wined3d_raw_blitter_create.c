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
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_blitter {struct wined3d_blitter* next; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 size_t ARB_COPY_IMAGE ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_blitter*) ; 
 struct wined3d_blitter* heap_alloc (int) ; 
 int /*<<< orphan*/  raw_blitter_ops ; 

void wined3d_raw_blitter_create(struct wined3d_blitter **next, const struct wined3d_gl_info *gl_info)
{
    struct wined3d_blitter *blitter;

    if (!gl_info->supported[ARB_COPY_IMAGE])
        return;

    if (!(blitter = heap_alloc(sizeof(*blitter))))
        return;

    TRACE("Created blitter %p.\n", blitter);

    blitter->ops = &raw_blitter_ops;
    blitter->next = *next;
    *next = blitter;
}