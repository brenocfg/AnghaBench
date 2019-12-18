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
struct vo_w32_state {int /*<<< orphan*/  window; int /*<<< orphan*/  input_ctx; int /*<<< orphan*/  current_fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTCAPTION ; 
 int MP_KEY_STATE_DOWN ; 
 int MP_KEY_STATE_UP ; 
 int MP_MBTN_LEFT ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NCLBUTTONDOWN ; 
 int mod_state (struct vo_w32_state*) ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_input_test_dragging (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool handle_mouse_down(struct vo_w32_state *w32, int btn, int x, int y)
{
    btn |= mod_state(w32);
    mp_input_put_key(w32->input_ctx, btn | MP_KEY_STATE_DOWN);

    if (btn == MP_MBTN_LEFT && !w32->current_fs &&
        !mp_input_test_dragging(w32->input_ctx, x, y))
    {
        // Window dragging hack
        ReleaseCapture();
        SendMessage(w32->window, WM_NCLBUTTONDOWN, HTCAPTION, 0);
        mp_input_put_key(w32->input_ctx, MP_MBTN_LEFT | MP_KEY_STATE_UP);

        // Indicate the message was handled, so DefWindowProc won't be called
        return true;
    }

    SetCapture(w32->window);
    return false;
}