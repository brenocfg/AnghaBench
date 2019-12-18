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
 int NUMBER_OF_ENCODERS ; 
 int* encoder_state ; 
 int /*<<< orphan*/  encoder_update (int,int) ; 
 int /*<<< orphan*/ * encoders_pad_a ; 
 int /*<<< orphan*/ * encoders_pad_b ; 
 int readPin (int /*<<< orphan*/ ) ; 
 int thisHand ; 

void encoder_read(void) {
    for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
        encoder_state[i] <<= 2;
        encoder_state[i] |= (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
#if SPLIT_KEYBOARD
        encoder_update(i + thisHand, encoder_state[i]);
#else
        encoder_update(i, encoder_state[i]);
#endif
    }
}