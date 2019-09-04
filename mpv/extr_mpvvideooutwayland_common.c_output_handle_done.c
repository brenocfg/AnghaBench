#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wl_output {int dummy; } ;
struct TYPE_3__ {scalar_t__ y0; scalar_t__ x0; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct vo_wayland_output {int /*<<< orphan*/  refresh_rate; int /*<<< orphan*/  scale; int /*<<< orphan*/  phys_height; TYPE_1__ geometry; int /*<<< orphan*/  phys_width; int /*<<< orphan*/  id; int /*<<< orphan*/  model; int /*<<< orphan*/  make; int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_rect_h (TYPE_1__) ; 
 int /*<<< orphan*/  mp_rect_w (TYPE_1__) ; 

__attribute__((used)) static void output_handle_done(void* data, struct wl_output *wl_output)
{
    struct vo_wayland_output *o = data;

    o->geometry.x1 += o->geometry.x0;
    o->geometry.y1 += o->geometry.y0;

    MP_VERBOSE(o->wl, "Registered output %s %s (0x%x):\n"
               "\tx: %dpx, y: %dpx\n"
               "\tw: %dpx (%dmm), h: %dpx (%dmm)\n"
               "\tscale: %d\n"
               "\tHz: %f\n", o->make, o->model, o->id, o->geometry.x0,
               o->geometry.y0, mp_rect_w(o->geometry), o->phys_width,
               mp_rect_h(o->geometry), o->phys_height, o->scale, o->refresh_rate);
}