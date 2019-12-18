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
struct vo_x11_state {scalar_t__ dnd_requested_format; scalar_t__ dnd_src_window; } ;
struct vo {struct vo_x11_state* x11; } ;

/* Variables and functions */

__attribute__((used)) static void dnd_reset(struct vo *vo)
{
    struct vo_x11_state *x11 = vo->x11;

    x11->dnd_src_window = 0;
    x11->dnd_requested_format = 0;
}