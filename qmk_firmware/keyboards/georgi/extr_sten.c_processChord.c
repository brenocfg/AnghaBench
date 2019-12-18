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
typedef  int uint32_t ;

/* Variables and functions */
 int FN ; 
 int PWR ; 
 int QWERBUF ; 
 int cChord ; 
 int chordIndex ; 
 int* chordState ; 
 int processFakeSteno (int) ; 
 int processQwerty (int) ; 
 int repeatFlag ; 
 int /*<<< orphan*/  restoreState () ; 
 int /*<<< orphan*/  saveState (int) ; 
 int stickyBits ; 

void processChord(bool useFakeSteno) {
	// Save the clean chord state
	uint32_t savedChord = cChord;

	// Apply Stick Bits if needed
	if (stickyBits != 0) {
		cChord |= stickyBits;
		for (int i = 0; i <= chordIndex; i++)
			chordState[i] |= stickyBits;
	}

	// Strip FN
	if (cChord & FN) cChord ^= FN;

	// First we test if a whole chord was passsed
	// If so we just run it handling repeat logic
	if (useFakeSteno && processFakeSteno(true) == cChord) {
		processFakeSteno(false);
		return;
	} else if (processQwerty(true) == cChord) {
		processQwerty(false);
		// Repeat logic
		if (repeatFlag) {
			restoreState();
			repeatFlag = false;
			processChord(false);
		} else {
			saveState(cChord);
		}
		return;
	}

	// Iterate through chord picking out the individual 
	// and longest chords
	uint32_t bufChords[QWERBUF];
	int 	 bufLen		= 0;
	uint32_t mask		= 0;

	// We iterate over it multiple times to catch the longest
	// chord. Then that gets addded to the mask and re run.
	while (savedChord != mask) {
		uint32_t test  	 		= 0;
		uint32_t longestChord	= 0;

		for (int i = 0; i <= chordIndex; i++) {
			cChord = chordState[i] & ~mask;
			if (cChord == 0)
				continue;

			// Assume mid parse Sym is new chord
			if (i != 0 && test != 0 && (cChord ^ test) == PWR) {
				longestChord = test;
				break;
			}

			// Lock SYM layer in once detected
			if (mask & PWR)
				cChord |= PWR;


			// Testing for keycodes
			if (useFakeSteno) {
				test = processFakeSteno(true);
			} else {
				test = processQwerty(true);
			}
		 
			if (test != 0) {
				longestChord = test;
			}
		}
		
		mask |= longestChord;
		bufChords[bufLen] = longestChord;
		bufLen++;

		// That's a loop of sorts, halt processing
		if (bufLen >= QWERBUF) {
			return;
		}
	}
	
	// Now that the buffer is populated, we run it
	for (int i = 0; i < bufLen ; i++) {
		cChord = bufChords[i];
		if (useFakeSteno) {
			processFakeSteno(false);
		} else {
			processQwerty(false);
		}
	}

	// Save state in case of repeat
	if (!repeatFlag) {			
		saveState(savedChord);
	}

	// Restore cChord for held repeat
	cChord = savedChord;

	return;
}