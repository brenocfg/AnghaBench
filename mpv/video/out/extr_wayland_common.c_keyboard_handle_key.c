#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xkb_mod_index_t ;
typedef  int /*<<< orphan*/  xkb_keysym_t ;
typedef  scalar_t__ uint32_t ;
struct wl_keyboard {int dummy; } ;
struct vo_wayland_state {TYPE_1__* vo; int /*<<< orphan*/  xkb_state; int /*<<< orphan*/  xkb_keymap; } ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_2__ {int /*<<< orphan*/  input_ctx; } ;

/* Variables and functions */
#define  MP_KEY_MODIFIER_ALT 135 
#define  MP_KEY_MODIFIER_CTRL 134 
#define  MP_KEY_MODIFIER_META 133 
#define  MP_KEY_MODIFIER_SHIFT 132 
 int MP_KEY_STATE_DOWN ; 
 int MP_KEY_STATE_UP ; 
 scalar_t__ WL_KEYBOARD_KEY_STATE_PRESSED ; 
#define  XKB_MOD_NAME_ALT 131 
#define  XKB_MOD_NAME_CTRL 130 
#define  XKB_MOD_NAME_LOGO 129 
#define  XKB_MOD_NAME_SHIFT 128 
 int /*<<< orphan*/  XKB_STATE_MODS_DEPRESSED ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 scalar_t__ code ; 
 int lookupkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_input_put_key_utf8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_keymap_mod_get_index (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ xkb_keysym_to_utf8 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xkb_state_key_get_one_sym (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ xkb_state_mod_index_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_state_mod_index_is_consumed (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyboard_handle_key(void *data, struct wl_keyboard *wl_keyboard,
                                uint32_t serial, uint32_t time, uint32_t key,
                                uint32_t state)
{
    struct vo_wayland_state *wl = data;

    uint32_t code = code = key + 8;
    xkb_keysym_t sym = xkb_state_key_get_one_sym(wl->xkb_state, code);

    int mpmod = state == WL_KEYBOARD_KEY_STATE_PRESSED ? MP_KEY_STATE_DOWN
                                                       : MP_KEY_STATE_UP;

    static const char *mod_names[] = {
        XKB_MOD_NAME_SHIFT,
        XKB_MOD_NAME_CTRL,
        XKB_MOD_NAME_ALT,
        XKB_MOD_NAME_LOGO,
        0,
    };

    static int mods[] = {
        MP_KEY_MODIFIER_SHIFT,
        MP_KEY_MODIFIER_CTRL,
        MP_KEY_MODIFIER_ALT,
        MP_KEY_MODIFIER_META,
        0,
    };

    for (int n = 0; mods[n]; n++) {
        xkb_mod_index_t index = xkb_keymap_mod_get_index(wl->xkb_keymap, mod_names[n]);
        if (!xkb_state_mod_index_is_consumed(wl->xkb_state, code, index)
            && xkb_state_mod_index_is_active(wl->xkb_state, index,
                                             XKB_STATE_MODS_DEPRESSED))
            mpmod |= mods[n];
    }

    int mpkey = lookupkey(sym);
    if (mpkey) {
        mp_input_put_key(wl->vo->input_ctx, mpkey | mpmod);
    } else {
        char s[128];
        if (xkb_keysym_to_utf8(sym, s, sizeof(s)) > 0)
            mp_input_put_key_utf8(wl->vo->input_ctx, mpmod, bstr0(s));
    }
}