#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * dpy; } ;
typedef  TYPE_1__ xcursor_t ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 TYPE_1__* bzalloc (int) ; 
 int /*<<< orphan*/  xcursor_tick (TYPE_1__*) ; 

xcursor_t *xcursor_init(Display *dpy)
{
	xcursor_t *data = bzalloc(sizeof(xcursor_t));

	data->dpy = dpy;
	xcursor_tick(data);

	return data;
}