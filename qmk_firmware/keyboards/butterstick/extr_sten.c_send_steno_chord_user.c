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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  steno_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CMDBUF ; 
 int CMDLEN ; 
 scalar_t__ COMMAND ; 
 int FN ; 
 int PWR ; 
 int QWERSTENO ; 
 scalar_t__ QWERTY ; 
 int RD ; 
 int RZ ; 
 int ST1 ; 
 int ST2 ; 
 int ST3 ; 
 int ST4 ; 
 scalar_t__ STENO ; 
 int cChord ; 
 scalar_t__ cMode ; 
 scalar_t__ chordIndex ; 
 int* chordState ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int inChord ; 
 int inMouse ; 
 int keymapsCount ; 
 int /*<<< orphan*/  layer_on (int) ; 
 int /*<<< orphan*/  mousePress ; 
 int /*<<< orphan*/  mousekey_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousekey_send () ; 
 scalar_t__ pMode ; 
 int /*<<< orphan*/  processChord (int) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int repEngaged ; 
 int /*<<< orphan*/  uprintf (char*) ; 

bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) { 
	// Check for mousekeys, this is release
#ifdef MOUSEKEY_ENABLE
	if (inMouse) {
		inMouse = false;
		mousekey_off(mousePress);
		mousekey_send();
	}
#endif

	// Toggle Serial/QWERTY steno
	if (cChord == (PWR | FN | ST1 | ST2)) {
#ifndef NO_DEBUG
		uprintf("Fallback Toggle\n");
#endif
		QWERSTENO = !QWERSTENO;
		
		goto out;
	}

	// handle command mode
	if (cChord == (PWR | FN | RD | RZ)) {
#ifndef NO_DEBUG
		uprintf("COMMAND Toggle\n");
#endif
		if (cMode != COMMAND) {   // Entering Command Mode
			CMDLEN = 0;
			pMode = cMode;
			cMode = COMMAND;
		} else {                  // Exiting Command Mode
			cMode = pMode;

			// Press all and release all
			for (int i = 0; i < CMDLEN; i++) {
				register_code(CMDBUF[i]);
			}
			clear_keyboard();
		}

		goto out;
	}

	// Handle Gaming Toggle,
	if (cChord == (PWR | FN | ST4 | ST3) && keymapsCount > 1) {
#ifndef NO_DEBUG
		uprintf("Switching to QMK\n");
#endif
		layer_on(1);
		goto out;
	}

	// Lone FN press, toggle QWERTY
#ifndef ONLYQWERTY
	if (cChord == FN) {
		(cMode == STENO) ? (cMode = QWERTY) : (cMode = STENO);
		goto out;
	}
#endif

	// Check for Plover momentary
	if (cMode == QWERTY && (cChord & FN)) {
		cChord ^= FN;
		goto steno;
	}

	// Do QWERTY and Momentary QWERTY
	if (cMode == QWERTY || (cMode == COMMAND) || (cChord & (FN | PWR))) {
		processChord(false);
		goto out;
	}

	// Fallback NKRO Steno
	if (cMode == STENO && QWERSTENO) {
		processChord(true);
		goto out;
	}

steno:
	// Hey that's a steno chord!
	inChord = false;
	chordIndex = 0;
	cChord = 0;
	return true; 

out:
	cChord = 0;
	inChord = false;
	chordIndex = 0;
	clear_keyboard();
	repEngaged  = false;
	for (int i = 0; i < 32; i++)
		chordState[i] = 0xFFFF;

	return false;
}