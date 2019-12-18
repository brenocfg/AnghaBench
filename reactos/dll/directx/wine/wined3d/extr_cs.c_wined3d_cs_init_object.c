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
struct wined3d_cs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wined3d_cs_emit_callback (struct wined3d_cs*,void (*) (void*),void*) ; 

void wined3d_cs_init_object(struct wined3d_cs *cs, void (*callback)(void *object), void *object)
{
    wined3d_cs_emit_callback(cs, callback, object);
}