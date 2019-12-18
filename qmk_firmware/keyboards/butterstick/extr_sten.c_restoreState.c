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
 int /*<<< orphan*/  cChord ; 
 int /*<<< orphan*/  chordIndex ; 
 int /*<<< orphan*/ * chordState ; 
 int /*<<< orphan*/  pChord ; 
 int /*<<< orphan*/  pChordIndex ; 
 int /*<<< orphan*/ * pChordState ; 

void restoreState() {
	cChord = pChord;
	chordIndex = pChordIndex;
	for (int i = 0; i < 32; i++) 
		chordState[i] = pChordState[i];
}