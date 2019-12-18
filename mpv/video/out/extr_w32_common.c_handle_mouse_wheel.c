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
struct vo_w32_state {int /*<<< orphan*/  input_ctx; } ;

/* Variables and functions */
 int MP_WHEEL_DOWN ; 
 int MP_WHEEL_LEFT ; 
 int MP_WHEEL_RIGHT ; 
 int MP_WHEEL_UP ; 
 int abs (int) ; 
 int mod_state (struct vo_w32_state*) ; 
 int /*<<< orphan*/  mp_input_put_wheel (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void handle_mouse_wheel(struct vo_w32_state *w32, bool horiz, int val)
{
    int code;
    if (horiz)
        code = val > 0 ? MP_WHEEL_RIGHT : MP_WHEEL_LEFT;
    else
        code = val > 0 ? MP_WHEEL_UP : MP_WHEEL_DOWN;
    mp_input_put_wheel(w32->input_ctx, code | mod_state(w32), abs(val) / 120.);
}