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
struct wined3d_gl_info {int dummy; } ;
struct wined3d_blitter {struct wined3d_blitter* next; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct wined3d_blitter*) ; 
 int /*<<< orphan*/  ffp_blitter_ops ; 
 struct wined3d_blitter* heap_alloc (int) ; 

void wined3d_ffp_blitter_create(struct wined3d_blitter **next, const struct wined3d_gl_info *gl_info)
{
    struct wined3d_blitter *blitter;

    if (!(blitter = heap_alloc(sizeof(*blitter))))
        return;

    TRACE("Created blitter %p.\n", blitter);

    blitter->ops = &ffp_blitter_ops;
    blitter->next = *next;
    *next = blitter;
}