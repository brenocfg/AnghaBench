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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  pin_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ENCODERS_PAD_A_RIGHT ; 
 int /*<<< orphan*/ * ENCODERS_PAD_B_RIGHT ; 
 size_t NUMBER_OF_ENCODERS ; 
 int* encoder_state ; 
 int /*<<< orphan*/ * encoders_pad_a ; 
 int /*<<< orphan*/ * encoders_pad_b ; 
 scalar_t__ isLeftHand ; 
 int readPin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setPinInputHigh (int /*<<< orphan*/ ) ; 
 size_t thatHand ; 
 size_t thisHand ; 

void encoder_init(void) {
#if defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)
    if (!isLeftHand) {
        const pin_t encoders_pad_a_right[] = ENCODERS_PAD_A_RIGHT;
        const pin_t encoders_pad_b_right[] = ENCODERS_PAD_B_RIGHT;
        for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
            encoders_pad_a[i] = encoders_pad_a_right[i];
            encoders_pad_b[i] = encoders_pad_b_right[i];
        }
    }
#endif

    for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
        setPinInputHigh(encoders_pad_a[i]);
        setPinInputHigh(encoders_pad_b[i]);

        encoder_state[i] = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
    }

#ifdef SPLIT_KEYBOARD
    thisHand = isLeftHand ? 0 : NUMBER_OF_ENCODERS;
    thatHand = NUMBER_OF_ENCODERS - thisHand;
#endif
}