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
struct vo_x11_state {int win_drag_button1_down; int /*<<< orphan*/  input_ctx; scalar_t__ no_autorepeat; } ;
struct vo {struct vo_x11_state* x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INPUT_RELEASE_ALL ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_all_keys(struct vo *vo)
{
    struct vo_x11_state *x11 = vo->x11;

    if (x11->no_autorepeat)
        mp_input_put_key(x11->input_ctx, MP_INPUT_RELEASE_ALL);
    x11->win_drag_button1_down = false;
}