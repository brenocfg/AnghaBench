#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 scalar_t__ IS_STANDARD_KEYCODE (scalar_t__) ; 
 scalar_t__ KC_LOCK ; 
 scalar_t__ KEY_STATE (scalar_t__) ; 
 int /*<<< orphan*/  SET_KEY_STATE (scalar_t__) ; 
 int /*<<< orphan*/  UNSET_KEY_STATE (scalar_t__) ; 
 scalar_t__ translate_keycode (scalar_t__) ; 
 int watching ; 

bool process_key_lock(uint16_t *keycode, keyrecord_t *record) {
    // We start by categorizing the keypress event. In the event of a down
    // event, there are several possibilities:
    // 1. The key is not being locked, and we are not watching for new keys.
    //    In this case, we bail immediately. This is the common case for down events.
    // 2. The key was locked, and we need to unlock it. In this case, we will
    //    reset the state in our map and return false. When the user releases the
    //    key, the up event will no longer be masked and the OS will observe the
    //    released key.
    // 3. KC_LOCK was just pressed. In this case, we set up the state machine
    //    to watch for the next key down event, and finish processing
    // 4. The keycode is below 0xFF, and we are watching for new keys. In this case,
    //    we will send the key down event to the os, and set the key_state for that
    //    key to mask the up event.
    // 5. The keycode is above 0xFF, and we're wathing for new keys. In this case,
    //    the user pressed a key that we cannot "lock", as it's a series of keys,
    //    or a macro invocation, or a layer transition, or a custom-defined key, or
    //    or some other arbitrary code. In this case, we bail immediately, reset
    //    our watch state, and return true.
    //
    // In the event of an up event, there are these possibilities:
    // 1. The key is not being locked. In this case, we return true and bail
    //    immediately. This is the common case.
    // 2. The key is being locked. In this case, we will mask the up event
    //    by returning false, so the OS never sees that the key was released
    //    until the user pressed the key again.

    // We translate any OSM keycodes back to their original keycodes, so that if the key being
    // one-shot modded is a standard keycode, we can handle it. This is the only set of special
    // keys that we handle
    uint16_t translated_keycode = translate_keycode(*keycode);

    if (record->event.pressed) {
        // Non-standard keycode, reset and return
        if (!(IS_STANDARD_KEYCODE(translated_keycode) || translated_keycode == KC_LOCK)) {
            watching = false;
            return true;
        }

        // If we're already watching, turn off the watch.
        if (translated_keycode == KC_LOCK) {
            watching = !watching;
            return false;
        }

        if (IS_STANDARD_KEYCODE(translated_keycode)) {
            // We check watching first. This is so that in the following scenario, we continue to
            // hold the key: KC_LOCK, KC_F, KC_LOCK, KC_F
            // If we checked in reverse order, we'd end up holding the key pressed after the second
            // KC_F press is registered, when the user likely meant to hold F
            if (watching) {
                watching = false;
                SET_KEY_STATE(translated_keycode);
                // We need to set the keycode passed in to be the translated keycode, in case we
                // translated a OSM back to the original keycode.
                *keycode = translated_keycode;
                // Let the standard keymap send the keycode down event. The up event will be masked.
                return true;
            }

            if (KEY_STATE(translated_keycode)) {
                UNSET_KEY_STATE(translated_keycode);
                // The key is already held, stop this process. The up event will be sent when the user
                // releases the key.
                return false;
            }
        }

        // Either the key isn't a standard key, or we need to send the down event. Continue standard
        // processing
        return true;
    } else {
        // Stop processing if it's a standard key and we're masking up.
        return !(IS_STANDARD_KEYCODE(translated_keycode) && KEY_STATE(translated_keycode));
    }
}