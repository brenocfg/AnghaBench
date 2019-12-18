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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int PB0 ; 
 int PB1 ; 
 int PB2 ; 
 int PB3 ; 
 int PORTB ; 
 int biton32 (int /*<<< orphan*/ ) ; 

uint32_t layer_state_set_user(uint32_t state)
{
  // if on layer 0, turn on B0 LED, otherwise off.
    if (biton32(state) == 0) {
        PORTB &= ~(1<<PB0);
    } else {
        PORTB |= (1<<PB0);
    }

  // if on layer 1, turn on B1 LED, otherwise off.
    if (biton32(state) == 1) {
        PORTB &= ~(1<<PB1);
    } else {
        PORTB |= (1<<PB1);
    }
  // if on layer 2, turn on B2 LED, otherwise off.
    if (biton32(state) == 2) {
        PORTB &= ~(1<<PB2);
    } else {
        PORTB |= (1<<PB2);
    }

  // if on layer 3, turn on B3 LED, otherwise off.
    if (biton32(state) == 3) {
        PORTB &= ~(1<<PB3);
    } else {
        PORTB |= (1<<PB3);
    }

    return state;
}