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
 int MP_KEY_STATE_UP ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int mod_state (struct vo_w32_state*) ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handle_mouse_up(struct vo_w32_state *w32, int btn)
{
    btn |= mod_state(w32);
    mp_input_put_key(w32->input_ctx, btn | MP_KEY_STATE_UP);

    ReleaseCapture();
}