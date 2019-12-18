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

/* Variables and functions */
 int /*<<< orphan*/  BOLT_STATE_SIZE ; 
 int /*<<< orphan*/  GEMINI_STATE_SIZE ; 
#define  STENO_MODE_BOLT 129 
#define  STENO_MODE_GEMINI 128 
 int* chord ; 
 int mode ; 
 scalar_t__ send_steno_chord_user (int,int*) ; 
 int /*<<< orphan*/  send_steno_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  steno_clear_state () ; 
 int /*<<< orphan*/  virtser_send (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_steno_chord(void) {
    if (send_steno_chord_user(mode, chord)) {
        switch (mode) {
            case STENO_MODE_BOLT:
                send_steno_state(BOLT_STATE_SIZE, false);
                virtser_send(0);  // terminating byte
                break;
            case STENO_MODE_GEMINI:
                chord[0] |= 0x80;  // Indicate start of packet
                send_steno_state(GEMINI_STATE_SIZE, true);
                break;
        }
    }
    steno_clear_state();
}