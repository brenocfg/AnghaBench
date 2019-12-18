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
 int /*<<< orphan*/  DDRB ; 
 int /*<<< orphan*/  DDRC ; 
 int /*<<< orphan*/  PLAY_NOTE_ARRAY (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORTB ; 
 int /*<<< orphan*/  PORTC ; 
 int /*<<< orphan*/  STACCATO ; 
 int /*<<< orphan*/  audio_init () ; 
 int /*<<< orphan*/  cbi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  issi_init () ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  sbi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_sound ; 

void matrix_init_kb(void)
{
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();

#ifdef AUDIO_ENABLE
    audio_init();
    PLAY_NOTE_ARRAY(test_sound, false, STACCATO);
    // Fix port B5
    cbi(DDRB, 5);
    sbi(PORTB, 5);
#else
    // If we're not using the audio pin, drive it low
    sbi(DDRC, 6);
    cbi(PORTC, 6);
#endif
#ifdef ISSI_ENABLE
    issi_init();
#endif
}