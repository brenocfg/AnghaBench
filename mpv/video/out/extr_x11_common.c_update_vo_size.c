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
struct vo_x11_state {int /*<<< orphan*/  pending_vo_events; int /*<<< orphan*/  winrc; } ;
struct vo {scalar_t__ dwidth; scalar_t__ dheight; struct vo_x11_state* x11; } ;

/* Variables and functions */
 scalar_t__ RC_H (int /*<<< orphan*/ ) ; 
 scalar_t__ RC_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VO_EVENT_RESIZE ; 

__attribute__((used)) static void update_vo_size(struct vo *vo)
{
    struct vo_x11_state *x11 = vo->x11;

    if (RC_W(x11->winrc) != vo->dwidth || RC_H(x11->winrc) != vo->dheight) {
        vo->dwidth = RC_W(x11->winrc);
        vo->dheight = RC_H(x11->winrc);
        x11->pending_vo_events |= VO_EVENT_RESIZE;
    }
}